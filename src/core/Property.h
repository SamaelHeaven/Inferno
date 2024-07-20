#pragma once

#include "../inferno.h"

template<typename T>
using PropertySetter = std::function<void(const T &old_value, const T &new_value, const std::function<void(const T &t)> &set)>;

template<typename T>
using PropertyListener = std::function<void(const T &old_value, const T &new_value)>;

namespace inferno {
    template<typename T>
    class Property final {
    public:
        [[nodiscard]] T get() const;

        void set(const T &value);

        // ReSharper disable once CppNonExplicitConvertingConstructor
        Property( // NOLINT(*-explicit-constructor)
            const T &value,
            const PropertySetter<T> &setter = [](
                [[maybe_unused]] const auto &old_value, const auto &new_value, const auto &set) {
                set(new_value);
            }
        );

        void add_listener(const PropertyListener<T> &listener);

        void remove_listener(const PropertyListener<T> &listener);

    private:
        T value_;
        PropertySetter<T> setter_;
        mutable std::vector<PropertyListener<T> > listeners_;
    };

    template<typename T>
    T Property<T>::get() const {
        return value_;
    }

    template<typename T>
    void Property<T>::set(const T &value) {
        setter_(value_, value, [this](const T &t) {
            T old_value = value_;
            value_ = t;
            for (const auto &listener: listeners_) {
                listener(old_value, t);
            }
        });
    }

    template<typename T>
    Property<T>::Property(
        const T &value,
        const PropertySetter<T> &setter
    ) : value_(value), setter_(setter) {
    }

    template<typename T>
    void Property<T>::add_listener(const PropertyListener<T> &listener) {
        listeners_.insert(listener);
    }

    template<typename T>
    void Property<T>::remove_listener(const PropertyListener<T> &listener) {
        listeners_.erase(listener);
    }
}
