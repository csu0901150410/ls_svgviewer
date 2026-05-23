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
        static plugin_manager& instance();

        bool load_plugin(const char* path);

        ~plugin_manager();

    private:
        plugin_manager() = default;
        plugin_manager(const plugin_manager&);
        plugin_manager& operator=(const plugin_manager&);

    private:
        struct plugin_entry
        {
            shared_library library;
            plugin* instance;
        };

        std::vector<plugin_entry> plugins;
    };
}
