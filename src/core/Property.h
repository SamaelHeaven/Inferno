#pragma once

#include "../inferno.h"

namespace inferno {
    template <typename T> using PropertyListener = std::function<void(T, T)>;

    template <typename T> using PropertySetter = std::function<void(T, std::function<void(T)>)>;

    template <typename T> class Property {
    public:
        Property() = default;

        explicit Property(
            const T &value, PropertySetter<T> setter = [](const auto &v, const auto &s) {
                s(v);
            }) {
            value_ = value;
            setter_ = setter;
        }

        class Connection {
        public:
            ~Connection() {
                disconnect();
            }

            Connection &operator=(const Connection &) = delete;

            [[nodiscard]] bool connected() const {
                return connection_.has_value() && connection_.value().connected();
            }

            void disconnect() const {
                if (!connection_.has_value()) {
                    return;
                }
                if (const auto &connection = connection_.value(); connection.connected()) {
                    connection.disconnect();
                }
            }

        private:
            Connection() = default;

            explicit Connection(const boost::signals2::connection &connection) {
                connection_ = connection;
            }

            std::optional<boost::signals2::connection> connection_;

            friend class Property;
        };

        const T &get() const {
            return value_;
        }

        void set(const T &newValue) {
            auto oldValue = value_;
            setter_(newValue, [&](auto v) {
                value_ = v;
                on_changed_(oldValue, value_);
            });
        }

        Property(const Property &other) {
            value_ = other.value_;
            setter_ = [](const auto &v, const auto &s) {
                s(v);
            };
        }

        Property &operator=(const Property &other) {
            if (this == &other) {
                return *this;
            }
            set(other.value_);
            return *this;
        }

        Connection subscribe(const PropertyListener<T> &listener) const {
            return Connection(on_changed_.connect(listener));
        }

        void bind(Property &other) {
            unbind();
            other_binding_ = other.subscribe([&]([[maybe_unused]] const T &oldValue, const T &newValue) {
                this->set(newValue);
            });
        }

        void bindBidirectional(Property &other) {
            bind(other);
            reverse_binding_ = this->subscribe([&]([[maybe_unused]] const T &oldValue, const T &newValue) {
                other.set(newValue);
            });
        }

        void unbind() const {
            other_binding_.disconnect();
            reverse_binding_.disconnect();
        }

    private:
        T value_;

        PropertySetter<T> setter_;

        boost::signals2::signal<void(const T &, const T &)> on_changed_;

        Connection other_binding_;

        Connection reverse_binding_;
    };
}
