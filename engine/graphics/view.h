#pragma once

#include "graphics_api.h"
#include "input_event.h"

namespace graphics
{
    class GRAPHICS_API view
    {
    public:
        bool handle_event(const input_event& event);

        int handled_event_count() const;
        const input_event& last_event() const;

    private:
        input_event lastInputEvent;
        int eventCount = 0;
    };
}
