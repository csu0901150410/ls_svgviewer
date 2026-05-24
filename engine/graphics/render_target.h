#pragma once

#include "native_window.h"

namespace graphics
{
    struct render_target_desc
    {
        native_window_handle window = nullptr;
        int width = 0;
        int height = 0;
    };
}
