#pragma once

#include "../inferno.h"
#include "../math/random.h"

template<typename T>
using PropertySetter = std::function<void(const T &old_value, const T &new_value,const std::function<void(const T &t)> &set)>;

template<typename T>
using PropertyListener = std::function<void(const T &old_value, const T &new_value)>;

using PropertyListenerID = size_t;

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

        PropertyListenerID add_listener(const PropertyListener<T> &listener) const;

        void remove_listener(PropertyListenerID id) const;

    private:
        T value_;
        PropertySetter<T> setter_;
        mutable std::unordered_map<PropertyListenerID, PropertyListener<T> > listeners_;
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
            for (const auto &entry: listeners_) {
                entry.second(old_value, t);
            }
        });
    }

    template<typename T>
    Property<T>::Property(
        const T &value,
        const PropertySetter<T> &setter
    ) : value_(value), setter_(setter) {}

    template<typename T>
    PropertyListenerID Property<T>::add_listener(const PropertyListener<T> &listener) const {
        const auto id = random::uint64(0, UINT64_MAX);
        listeners_.emplace(id, listener);
        return id;
    }

    template<typename T>
    void Property<T>::remove_listener(PropertyListenerID id) const {
        listeners_.erase(id);
    }
}
