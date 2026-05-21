#include "plugin_manager.h"


#include <iostream>

#include "logger.h"

// 定义工厂函数指针类型
typedef core::plugin* (*create_plugin_func)();

namespace core
{
    plugin_manager::~plugin_manager()
    {
        
    }

    bool plugin_manager::load_plugin(const char* path)
    {
        if (!path)
            return false;

        // load dynamic library
        HMODULE hModule = LoadLibraryA(path);
        if (!hModule)
        {
            DWORD error = GetLastError();
            std::cerr << "Failed to load library: " << path 
                      << ", Error Code: " << error << std::endl;
            return false;
        }

        // find create_plugin symbol
        create_plugin_func createPlugin = (create_plugin_func)GetProcAddress(hModule, "create_plugin");
        if (!createPlugin)
        {
            DWORD error = GetLastError();
            std::cerr << "Failed to find symbol 'create_plugin' in: " << path 
                      << ", Error Code: " << error << std::endl;
            FreeLibrary(hModule);
            return false;
        }

        // create instance
        plugin* pluginInstance = createPlugin();
        if (!pluginInstance)
        {
            std::cerr << "Failed to create plugin instance from: " << path << std::endl;
            FreeLibrary(hModule);
            return false;
        }

        // store plugin instance
        plugins.push_back(pluginInstance);

        return true;
    }

}
