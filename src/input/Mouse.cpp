#include "./Mouse.h"

#include "../core/Game.h"
#include "../math/coordinates.h"

namespace inferno {
    std::set<MouseButton> Mouse::get_down_buttons() {
        return get_()->down_buttons_;
    }

    std::set<MouseButton> Mouse::get_up_buttons() {
        return get_()->up_buttons_;
    }

    std::set<MouseButton> Mouse::get_pressed_buttons() {
        return get_()->pressed_buttons_;
    }

    std::set<MouseButton> Mouse::get_released_buttons() {
        return get_()->released_buttons_;
    }

    bool Mouse::is_button_down(const MouseButton button) {
        return get_()->down_buttons_.contains(button);
    }

    bool Mouse::is_button_up(const MouseButton button) {
        return get_()->up_buttons_.contains(button);
    }

    bool Mouse::is_button_pressed(const MouseButton button) {
        return get_()->pressed_buttons_.contains(button);
    }

    bool Mouse::is_button_released(const MouseButton button) {
        return get_()->released_buttons_.contains(button);
    }

    Vector2 Mouse::get_position() {
        get_();
        return coordinates::screen_to_local(get_screen_position()).clamp(Vector2::ZERO, Game::get_size()).round();
    }

    void Mouse::set_position(Vector2 position) {
        get_();
        position = position.clamp(Vector2::ZERO, Game::get_size().round());
        if (get_position() == position) {
            return;
        }
        set_screen_position(coordinates::local_to_screen(position));
    }

    Vector2 Mouse::get_screen_position() {
        return get_()->screen_position_;
    }

    void Mouse::set_screen_position(Vector2 position) {
        const auto mouse = get_();
        if (!Game::is_focused()) {
            return;
        }
        position = position.clamp(Vector2::ZERO, Game::get_screen_size()).round();
        if (mouse->screen_position_ == position) {
            return;
        }
        mouse->screen_position_ = position;
        internal::SetMousePosition(static_cast<int32_t>(position.x), static_cast<int32_t>(position.y));
    }

    bool Mouse::is_on_screen() {
        get_();
        return internal::IsCursorOnScreen();
    }

    Cursor Mouse::get_cursor() {
        return get_()->cursor_;
    }

    void Mouse::set_cursor(const Cursor cursor) {
        const auto mouse = get_();
        if (cursor == mouse->cursor_) {
            return;
        }
        if (cursor == Cursor::NONE) {
            internal::HideCursor();
            mouse->cursor_ = cursor;
            return;
        }
        if (mouse->cursor_ == Cursor::NONE) {
            internal::ShowCursor();
        }
        internal::SetMouseCursor(static_cast<int32_t>(cursor));
        mouse->cursor_ = cursor;
    }

    Vector2 Mouse::get_scroll() {
        return get_()->scroll_;
    }

    Mouse::Mouse() {
        Game::throw_if_uninitialized();
        magic_enum::enum_for_each<MouseButton>([this](const MouseButton key) {
            buttons_.push_back(key);
        });
        cursor_ = Cursor::DEFAULT;
    }

    Mouse::~Mouse() = default;

    void Mouse::update_() {
        reset_state_();
        update_state_();
    }

    void Mouse::destroy_() {
        delete get_();
    }

    void Mouse::reset_state_() {
        const auto mouse = get_();
        mouse->scroll_ = Vector2::ZERO;
        mouse->down_buttons_.clear();
        mouse->up_buttons_.clear();
        mouse->pressed_buttons_.clear();
        mouse->released_buttons_.clear();
    }

    void Mouse::update_state_() {
        const auto mouse = get_();
        if (!Game::is_focused()) {
            for (auto button: mouse->buttons_) {
                mouse->up_buttons_.insert(button);
            }
            return;
        }
        const auto position = internal::GetMousePosition();
        const auto scroll = internal::GetMouseWheelMoveV();
        mouse->screen_position_ = Vector2(position.x, position.y).clamp(Vector2::ZERO, Game::get_screen_size()).round();
        mouse->scroll_ = {scroll.x, scroll.y};
        for (auto button: mouse->buttons_) {
            const auto button_code = static_cast<int32_t>(button);
            if (internal::IsMouseButtonDown(button_code)) {
                mouse->down_buttons_.insert(button);
            } else {
                mouse->up_buttons_.insert(button);
            }
            if (internal::IsMouseButtonPressed(button_code)) {
                mouse->pressed_buttons_.insert(button);
            }
            if (internal::IsMouseButtonReleased(button_code)) {
                mouse->released_buttons_.insert(button);
            }
        }
    }

    Mouse *Mouse::get_() {
        static Mouse *instance = nullptr;
        return instance = instance == nullptr ? new Mouse() : instance;
    }
}
