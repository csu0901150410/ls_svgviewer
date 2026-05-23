#pragma once

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
        plugin_manager(const plugin_manager&) = delete;
        plugin_manager& operator=(const plugin_manager&) = delete;

    private:
        struct plugin_entry
        {
            shared_library library;
            plugin* instance;
            void (*destroy)(plugin*);
        };

        std::vector<plugin_entry> plugins;
    };
}
