#pragma once

#include "color.h"

namespace graphics
{
    struct stroke_style
    {
        graphics::color color = graphics::color::rgba(0.0f, 0.0f, 0.0f);
        float width = 1.0f;
    };

    struct fill_style
    {
        graphics::color color = graphics::color::rgba(1.0f, 1.0f, 1.0f);
    };
}
