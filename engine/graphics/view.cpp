#include "view.h"

#include <iostream>

namespace
{
    const char* event_type_name(graphics::input_event_type type)
    {
        switch (type)
        {
        case graphics::input_event_type::mouse_down:
            return "mouse_down";
        case graphics::input_event_type::mouse_up:
            return "mouse_up";
        case graphics::input_event_type::mouse_move:
            return "mouse_move";
        case graphics::input_event_type::mouse_wheel:
            return "mouse_wheel";
        case graphics::input_event_type::key_down:
            return "key_down";
        case graphics::input_event_type::key_up:
            return "key_up";
        }

        return "unknown";
    }

    const char* mouse_button_name(graphics::mouse_button button)
    {
        switch (button)
        {
        case graphics::mouse_button::none:
            return "none";
        case graphics::mouse_button::left:
            return "left";
        case graphics::mouse_button::middle:
            return "middle";
        case graphics::mouse_button::right:
            return "right";
        }

        return "unknown";
    }
}

namespace graphics
{
    bool view::handle_event(const input_event& event)
    {
        lastInputEvent = event;
        ++eventCount;

        std::cout << "view input event type=" << event_type_name(event.type)
                  << " position=(" << event.position.x << ", " << event.position.y << ")"
                  << " button=" << mouse_button_name(event.button)
                  << " wheel_delta=" << event.wheel_delta
                  << " key=" << event.key
                  << " ctrl=" << event.modifiers.ctrl
                  << " shift=" << event.modifiers.shift
                  << " alt=" << event.modifiers.alt
                  << std::endl;

        return true;
    }

    int view::handled_event_count() const
    {
        return eventCount;
    }

    const input_event& view::last_event() const
    {
        return lastInputEvent;
    }
}
