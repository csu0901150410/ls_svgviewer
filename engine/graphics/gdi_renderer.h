#pragma once

#include "graphics_api.h"
#include "renderer.h"

namespace graphics
{
    class GRAPHICS_API gdi_renderer final : public renderer
    {
    public:
        gdi_renderer();
        ~gdi_renderer() override;

        gdi_renderer(const gdi_renderer&) = delete;
        gdi_renderer& operator=(const gdi_renderer&) = delete;

        bool attach(const render_target_desc& target) override;
        void begin_frame() override;
        void render(const scene& scene) override;
        void end_frame() override;

    private:
        void release_frame_resources();

    private:
        render_target_desc target;
        void* windowDc = nullptr;
        void* memoryDc = nullptr;
        void* bitmap = nullptr;
        void* oldBitmap = nullptr;
        bool frameActive = false;
    };
}
