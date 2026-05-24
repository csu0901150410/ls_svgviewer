#pragma once

#include "geometry.h"

namespace graphics
{
    enum class mouse_button
    {
        none,
        left,
        middle,
        right
    };

    enum class key_state
    {
        released,
        pressed
    };

    enum class input_event_type
    {
        mouse_down,
        mouse_up,
        mouse_move,
        mouse_wheel,
        key_down,
        key_up
    };

    struct key_modifiers
    {
        bool ctrl = false;
        bool shift = false;
        bool alt = false;
    };

    struct input_event
    {
        input_event_type type = input_event_type::mouse_move;
        point position;
        float wheel_delta = 0.0f;
        mouse_button button = mouse_button::none;
        int key = 0;
        key_modifiers modifiers;
    };
}
