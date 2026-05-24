#include "scene.h"

namespace graphics
{
    scene::scene() = default;

    scene::~scene() = default;

    scene::scene(scene&&) noexcept = default;

    scene& scene::operator=(scene&&) noexcept = default;

    void scene::add(std::unique_ptr<primitive> primitive)
    {
        if (!primitive)
            return;

        primitiveList.push_back(std::move(primitive));
    }

    void scene::clear()
    {
        primitiveList.clear();
    }

    const std::vector<std::unique_ptr<primitive>>& scene::primitives() const
    {
        return primitiveList;
    }
}
