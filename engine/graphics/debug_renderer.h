#pragma once

#include "graphics_api.h"
#include "renderer.h"

namespace graphics
{
    class GRAPHICS_API debug_renderer final : public renderer
    {
    public:
        void begin_frame() override;
        void render(const scene& scene) override;
        void end_frame() override;
    };
}
