#pragma once

namespace graphics
{
    struct color
    {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;

        static color rgba(float r, float g, float b, float a = 1.0f)
        {
            return {r, g, b, a};
        }
    };
}
