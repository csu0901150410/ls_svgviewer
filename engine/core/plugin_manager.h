#pragma once

#include <memory>
#include <vector>

#include <windows.h>

#include "core_api.h"
#include "plugin.h"

namespace core
{
    class CORE_API plugin_manager
    {
    public:
        bool load_plugin(const char* path);

        ~plugin_manager();

    private:
        std::vector<plugin*> plugins;
    };
}
