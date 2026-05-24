#pragma once

#include "render_target.h"
#include "scene.h"

namespace graphics
{
    class renderer
    {
    public:
        virtual ~renderer() = default;

        virtual bool attach(const render_target_desc& target) = 0;
        virtual void begin_frame() = 0;
        virtual void render(const scene& scene) = 0;
        virtual void end_frame() = 0;
    };
}
