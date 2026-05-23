#include "plugin_manager.h"

#include <iostream>

#include "logger.h"

// 定义工厂函数指针类型
typedef core::plugin* (*create_plugin_func)();
typedef void (*destroy_plugin_func)(core::plugin*);

namespace core
{
    plugin_manager& plugin_manager::instance()
    {
        static plugin_manager uniqueInstance;
        return uniqueInstance;
    }

    plugin_manager::~plugin_manager()
    {
        // 析构时调用动态库中的销毁函数销毁插件对象
        for (auto& entry : plugins)
        {
            if (entry.destroy && entry.instance)
                entry.destroy(entry.instance);
        }
        plugins.clear();
    }

    bool plugin_manager::load_plugin(const char* path)
    {
        if (!path)
            return false;

        // load dynamic library
        shared_library lib;
        if (!lib.load(path))
        {
            std::cerr << "Failed to load library: " << path << std::endl;
            return false;
        }

        // find create_plugin symbol
        auto createPlugin = (create_plugin_func)lib.get_symbol("create_plugin");
        if (!createPlugin)
        {
            std::cerr << "Failed to find symbol 'create_plugin' in: " << path << std::endl;
            return false;
        }

        auto destroyPlugin = (destroy_plugin_func)lib.get_symbol("destroy_plugin");
        if (!destroyPlugin)
        {
            std::cerr << "Failed to find symbol 'destroy_plugin' in: " << path << std::endl;
            return false;
        }

        // create instance
        plugin* pluginInstance = createPlugin();
        if (!pluginInstance)
        {
            std::cerr << "Failed to create plugin instance from: " << path << std::endl;
            return false;
        }

        // store plugin instance
        plugins.push_back({std::move(lib), pluginInstance, destroyPlugin});

        std::cout << "Plugin loaded successfully: " << pluginInstance->name() << std::endl;
        return true;
    }

}
