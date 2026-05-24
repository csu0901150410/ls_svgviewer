#pragma once

#include <memory>
#include <vector>

#include "graphics_api.h"
#include "primitive.h"

namespace graphics
{
    class GRAPHICS_API scene
    {
    public:
        scene();
        ~scene();

        scene(const scene&) = delete;
        scene& operator=(const scene&) = delete;

        scene(scene&&) noexcept;
        scene& operator=(scene&&) noexcept;

        void add(std::unique_ptr<primitive> primitive);
        void clear();

        const std::vector<std::unique_ptr<primitive>>& primitives() const;

    private:
        std::vector<std::unique_ptr<primitive>> primitiveList;
    };
}
