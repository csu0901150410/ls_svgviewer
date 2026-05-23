#pragma once

// plugin 模块被显式链接，只需要编译dll时dllexport

#ifdef _WIN32
    #define PLUGIN_API __declspec(dllexport)
#else
    #define PLUGIN_API __attribute__((visibility("default")))
#endif
