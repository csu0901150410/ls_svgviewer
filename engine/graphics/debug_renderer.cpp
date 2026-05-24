#include "debug_renderer.h"

#include <iostream>

namespace
{
    void print_color(const graphics::color& color)
    {
        std::cout << "rgba(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
    }

    void print_stroke(const graphics::stroke_style& stroke)
    {
        std::cout << " stroke=";
        print_color(stroke.color);
        std::cout << " stroke_width=" << stroke.width;
    }

    void print_fill(const graphics::fill_style& fill)
    {
        std::cout << " fill=";
        print_color(fill.color);
    }
}

namespace graphics
{
    bool debug_renderer::attach(const render_target_desc& target)
    {
        if (!target.window || target.width <= 0 || target.height <= 0)
            return false;

        this->target = target;
        std::cout << "attach render target window=" << target.window
                  << " width=" << target.width
                  << " height=" << target.height << std::endl;
        return true;
    }

    void debug_renderer::begin_frame()
    {
        std::cout << "begin frame target=(" << target.width << "x" << target.height << ")" << std::endl;
    }

    void debug_renderer::render(const scene& scene)
    {
        for (const auto& primitive : scene.primitives())
        {
            switch (primitive->type())
            {
            case primitive_type::line:
            {
                const auto& line = static_cast<const line_primitive&>(*primitive);
                std::cout << "draw line from=(" << line.from.x << ", " << line.from.y << ")"
                          << " to=(" << line.to.x << ", " << line.to.y << ")";
                print_stroke(line.stroke);
                std::cout << std::endl;
                break;
            }
            case primitive_type::rectangle:
            {
                const auto& rectangle = static_cast<const rect_primitive&>(*primitive);
                std::cout << "draw rect x=" << rectangle.bounds.x
                          << " y=" << rectangle.bounds.y
                          << " width=" << rectangle.bounds.width
                          << " height=" << rectangle.bounds.height;
                print_fill(rectangle.fill);
                print_stroke(rectangle.stroke);
                std::cout << std::endl;
                break;
            }
            case primitive_type::ellipse:
            {
                const auto& ellipse = static_cast<const ellipse_primitive&>(*primitive);
                std::cout << "draw ellipse center=(" << ellipse.center.x << ", " << ellipse.center.y << ")"
                          << " radius=(" << ellipse.radius.width << ", " << ellipse.radius.height << ")";
                print_fill(ellipse.fill);
                print_stroke(ellipse.stroke);
                std::cout << std::endl;
                break;
            }
            }
        }
    }

    void debug_renderer::end_frame()
    {
        std::cout << "end frame" << std::endl;
    }
}
