#pragma once

#include <memory>
#include <vector>

#include "core_api.h"
#include "plugin.h"
#include "platform.h"

namespace core
{
    class CORE_API plugin_manager
    {
    public:
        bool load_plugin(const char* path);

        ~plugin_manager();

    private:
        struct plugin_entry
        {
            shared_library library;
            plugin* instance;
        };

        std::vector<plugin_entry> plugins;
    };
}
