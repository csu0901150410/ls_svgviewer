#pragma once

#include "geometry.h"
#include "paint.h"

namespace graphics
{
    enum class primitive_type
    {
        line,
        rectangle,
        ellipse
    };

    class primitive
    {
    public:
        virtual ~primitive() = default;

        virtual primitive_type type() const = 0;
    };

    class line_primitive final : public primitive
    {
    public:
        line_primitive(point from, point to, stroke_style stroke)
            : from(from), to(to), stroke(stroke)
        {
        }

        primitive_type type() const override
        {
            return primitive_type::line;
        }

        point from;
        point to;
        stroke_style stroke;
    };

    class rect_primitive final : public primitive
    {
    public:
        rect_primitive(rect bounds, fill_style fill, stroke_style stroke)
            : bounds(bounds), fill(fill), stroke(stroke)
        {
        }

        primitive_type type() const override
        {
            return primitive_type::rectangle;
        }

        rect bounds;
        fill_style fill;
        stroke_style stroke;
    };

    class ellipse_primitive final : public primitive
    {
    public:
        ellipse_primitive(point center, size radius, fill_style fill, stroke_style stroke)
            : center(center), radius(radius), fill(fill), stroke(stroke)
        {
        }

        primitive_type type() const override
        {
            return primitive_type::ellipse;
        }

        point center;
        size radius;
        fill_style fill;
        stroke_style stroke;
    };
}
