#pragma once

// core 模块被隐式链接，编译dll时是dllexport，链接dll时是dllimport

#ifdef _WIN32
    #ifdef CORE_BUILDING_DLL
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#else
    #define CORE_API
#endif
