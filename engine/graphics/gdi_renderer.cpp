#include "gdi_renderer.h"

#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{
    int to_int(float value)
    {
        return static_cast<int>(std::lround(value));
    }

#ifdef _WIN32
    COLORREF to_color_ref(const graphics::color& color)
    {
        const auto clamp = [](float value) -> int {
            if (value < 0.0f)
                return 0;
            if (value > 1.0f)
                return 255;
            return to_int(value * 255.0f);
        };

        return RGB(clamp(color.r), clamp(color.g), clamp(color.b));
    }

    HPEN create_pen(const graphics::stroke_style& stroke)
    {
        const int width = stroke.width <= 0.0f ? 1 : to_int(stroke.width);
        return CreatePen(PS_SOLID, width, to_color_ref(stroke.color));
    }

    HBRUSH create_brush(const graphics::fill_style& fill)
    {
        return CreateSolidBrush(to_color_ref(fill.color));
    }
#endif
}

namespace graphics
{
    gdi_renderer::gdi_renderer() = default;

    gdi_renderer::~gdi_renderer()
    {
        release_frame_resources();
    }

    bool gdi_renderer::attach(const render_target_desc& target)
    {
        if (!target.window || target.width <= 0 || target.height <= 0)
            return false;

        this->target = target;
        return true;
    }

    void gdi_renderer::begin_frame()
    {
        release_frame_resources();

#ifdef _WIN32
        auto* hwnd = static_cast<HWND>(target.window);
        auto* hdc = GetDC(hwnd);
        if (!hdc)
            return;

        auto* memDc = CreateCompatibleDC(hdc);
        auto* backBuffer = CreateCompatibleBitmap(hdc, target.width, target.height);
        if (!memDc || !backBuffer)
        {
            if (backBuffer)
                DeleteObject(backBuffer);
            if (memDc)
                DeleteDC(memDc);
            ReleaseDC(hwnd, hdc);
            return;
        }

        auto* previousBitmap = SelectObject(memDc, backBuffer);

        RECT rect{0, 0, target.width, target.height};
        auto* background = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(memDc, &rect, background);
        DeleteObject(background);

        windowDc = hdc;
        memoryDc = memDc;
        bitmap = backBuffer;
        oldBitmap = previousBitmap;
        frameActive = true;
#endif
    }

    void gdi_renderer::render(const scene& scene)
    {
        if (!frameActive)
            return;

#ifdef _WIN32
        auto* hdc = static_cast<HDC>(memoryDc);

        for (const auto& primitive : scene.primitives())
        {
            switch (primitive->type())
            {
            case primitive_type::line:
            {
                const auto& line = static_cast<const line_primitive&>(*primitive);
                auto* pen = create_pen(line.stroke);
                auto* oldPen = SelectObject(hdc, pen);

                MoveToEx(hdc, to_int(line.from.x), to_int(line.from.y), nullptr);
                LineTo(hdc, to_int(line.to.x), to_int(line.to.y));

                SelectObject(hdc, oldPen);
                DeleteObject(pen);
                break;
            }
            case primitive_type::rectangle:
            {
                const auto& rectangle = static_cast<const rect_primitive&>(*primitive);
                auto* pen = create_pen(rectangle.stroke);
                auto* brush = create_brush(rectangle.fill);
                auto* oldPen = SelectObject(hdc, pen);
                auto* oldBrush = SelectObject(hdc, brush);

                Rectangle(
                    hdc,
                    to_int(rectangle.bounds.x),
                    to_int(rectangle.bounds.y),
                    to_int(rectangle.bounds.x + rectangle.bounds.width),
                    to_int(rectangle.bounds.y + rectangle.bounds.height));

                SelectObject(hdc, oldBrush);
                SelectObject(hdc, oldPen);
                DeleteObject(brush);
                DeleteObject(pen);
                break;
            }
            case primitive_type::ellipse:
            {
                const auto& ellipse = static_cast<const ellipse_primitive&>(*primitive);
                auto* pen = create_pen(ellipse.stroke);
                auto* brush = create_brush(ellipse.fill);
                auto* oldPen = SelectObject(hdc, pen);
                auto* oldBrush = SelectObject(hdc, brush);

                Ellipse(
                    hdc,
                    to_int(ellipse.center.x - ellipse.radius.width),
                    to_int(ellipse.center.y - ellipse.radius.height),
                    to_int(ellipse.center.x + ellipse.radius.width),
                    to_int(ellipse.center.y + ellipse.radius.height));

                SelectObject(hdc, oldBrush);
                SelectObject(hdc, oldPen);
                DeleteObject(brush);
                DeleteObject(pen);
                break;
            }
            }
        }
#else
        (void)scene;
#endif
    }

    void gdi_renderer::end_frame()
    {
        if (!frameActive)
            return;

#ifdef _WIN32
        BitBlt(
            static_cast<HDC>(windowDc),
            0,
            0,
            target.width,
            target.height,
            static_cast<HDC>(memoryDc),
            0,
            0,
            SRCCOPY);
#endif

        release_frame_resources();
    }

    void gdi_renderer::release_frame_resources()
    {
#ifdef _WIN32
        if (memoryDc && oldBitmap)
            SelectObject(static_cast<HDC>(memoryDc), static_cast<HGDIOBJ>(oldBitmap));

        if (bitmap)
            DeleteObject(static_cast<HBITMAP>(bitmap));

        if (memoryDc)
            DeleteDC(static_cast<HDC>(memoryDc));

        if (windowDc && target.window)
            ReleaseDC(static_cast<HWND>(target.window), static_cast<HDC>(windowDc));
#endif

        windowDc = nullptr;
        memoryDc = nullptr;
        bitmap = nullptr;
        oldBitmap = nullptr;
        frameActive = false;
    }
}
