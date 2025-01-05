#pragma once

#include "../inferno.h"

template <typename T>
using PropertySetter = std::function<void(const T &value, const std::function<void(const T &t)> &set)>;

template <typename T> using PropertyListener = std::function<void(const T &old_value, const T &new_value)>;

using PropertyListenerID = int32_t;

namespace inferno {
    template <typename T> class Property final {
    public:
        explicit Property(
            const T &value, const PropertySetter<T> &setter = [](const auto &v, const auto &s) {
                s(v);
            });

        ~Property();

        Property &operator=(const Property &property) = delete;

        [[nodiscard]] T get() const;

        void set(const T &value);

        PropertyListenerID add_listener(const PropertyListener<T> &listener) const;

        void remove_listener(PropertyListenerID id) const;

        void bind(const Property &other);

        void bind_bidirectional(Property &other);

        void unbind();

    private:
        inline static std::unordered_map<size_t, Property *> properties_;
        T value_;
        PropertySetter<T> setter_;
        mutable PropertyListenerID current_listener_id_ = -1;
        mutable std::unordered_map<PropertyListenerID, PropertyListener<T>> listeners_;
        Property *bound_property_ = nullptr;
        PropertyListenerID bound_listener_id_ = -1;
    };

    template <typename T>
    Property<T>::Property(const T &value, const PropertySetter<T> &setter) : value_(value), setter_(setter) {
        properties_[reinterpret_cast<size_t>(this)] = this;
    }

    template <typename T> Property<T>::~Property() {
        properties_.erase(reinterpret_cast<size_t>(this));
        unbind();
    }

    template <typename T> T Property<T>::get() const {
        return value_;
    }

    template <typename T> void Property<T>::set(const T &value) {
        if (value_ == value) {
            return;
        }
        setter_(value, [this](const T &t) {
            T old_value = value_;
            value_ = t;
            for (const auto &entry : listeners_) {
                entry.second(old_value, t);
            }
        });
    }

    template <typename T> PropertyListenerID Property<T>::add_listener(const PropertyListener<T> &listener) const {
        const auto id = ++current_listener_id_;
        listeners_.emplace(id, listener);
        return id;
    }

    template <typename T> void Property<T>::remove_listener(PropertyListenerID id) const {
        listeners_.erase(id);
    }

    template <typename T> void Property<T>::bind(const Property &other) {
        if (&other == this) {
            return;
        }
        unbind();
        bound_property_ = const_cast<Property *>(&other);
        bound_listener_id_ = other.add_listener([this]([[maybe_unused]] const T &old_value, const T &new_value) {
            set(new_value);
        });
        set(other.value_);
    }

    template <typename T> void Property<T>::bind_bidirectional(Property &other) {
        bind(other);
        other.bind(*this);
    }

    template <typename T> void Property<T>::unbind() {
        if (!bound_property_) {
            return;
        }
        if (properties_.contains(reinterpret_cast<size_t>(bound_property_))) {
            bound_property_->remove_listener(bound_listener_id_);
        }
        bound_property_ = nullptr;
        bound_listener_id_ = -1;
    }
}
