#pragma once

#include "scene.h"

namespace graphics
{
    class renderer
    {
    public:
        virtual ~renderer() = default;

        virtual void begin_frame() = 0;
        virtual void render(const scene& scene) = 0;
        virtual void end_frame() = 0;
    };
}
