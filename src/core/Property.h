#pragma once

#include "../inferno.h"

namespace inferno {
    template <typename T>
    using PropertySetter = std::function<void(const T &value, const std::function<void(const T &t)> &set)>;

    template <typename T> using PropertyListener = std::function<void(const T &old_value, const T &new_value)>;

    enum class PropertyListenerID : int32_t;

    template <typename T> class Property final {
    public:
        class Subscriber {
        public:
            ~Subscriber() {
                property_->listeners_.erase(listener_id_);
            }

        private:
            explicit Subscriber(const Property *property, const PropertyListenerID listener_id) {
                property_ = property;
                listener_id_ = listener_id;
            }

            const Property *property_;

            PropertyListenerID listener_id_;

            friend class Property;
        };

        explicit Property(
            const T &value, const PropertySetter<T> &setter = [](const auto &v, const auto &s) {
                s(v);
            });

        ~Property();

        Property(const Property &);

        Property &operator=(const Property &);

        [[nodiscard]] const T &get() const;

        void set(const T &value);

        Subscriber subscribe(const PropertyListener<T> &listener) const;

        void bind(const Property &other);

        void bind_bidirectional(Property &other);

        void unbind();

    private:
        inline static auto current_listener_id_ = static_cast<PropertyListenerID>(0);

        T value_;

        PropertySetter<T> setter_;

        mutable std::unordered_map<PropertyListenerID, PropertyListener<T>> listeners_;

        std::optional<Subscriber> bound_subscriber_;

        friend class Subscriber;

        friend class Scene;
    };

    template <typename T> Property<T>::Property(const T &value, const PropertySetter<T> &setter) {
        value_ = value;
        setter_ = setter;
    }

    template <typename T> Property<T>::~Property() {
        unbind();
    }

    template <typename T> Property<T>::Property(const Property &other) {
        value_ = other.value_;
        setter_ = [](const auto &v, const auto &s) {
            s(v);
        };
    }

    template <typename T> Property<T> &Property<T>::operator=(const Property &other) {
        if (&other == this) {
            return *this;
        }
        set(other.value_);
        return *this;
    }

    template <typename T> const T &Property<T>::get() const {
        return value_;
    }

    template <typename T> void Property<T>::set(const T &value) {
        if (value_ == value) {
            return;
        }
        setter_(value, [&](const T &t) {
            T old_value = value_;
            value_ = t;
            for (const auto &entry : listeners_) {
                entry.second(old_value, t);
            }
        });
    }

    template <typename T>
    typename Property<T>::Subscriber Property<T>::subscribe(const PropertyListener<T> &listener) const {
        current_listener_id_ = static_cast<PropertyListenerID>(static_cast<int32_t>(current_listener_id_) + 1);
        const PropertyListenerID listener_id = current_listener_id_;
        listeners_.emplace(listener_id, listener);
        return Subscriber(this, listener_id);
    }

    template <typename T> void Property<T>::bind(const Property &other) {
        if (&other == this) {
            return;
        }
        unbind();
        bound_subscriber_ = other.subscribe([&]([[maybe_unused]] const T &old_value, const T &new_value) {
            set(new_value);
        });
        set(other.value_);
    }

    template <typename T> void Property<T>::bind_bidirectional(Property &other) {
        bind(other);
        other.bind(this);
    }

    template <typename T> void Property<T>::unbind() {
        if (bound_subscriber_.has_value()) {
            bound_subscriber_.reset();
        }
    }
}