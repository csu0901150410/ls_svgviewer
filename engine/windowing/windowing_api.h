#pragma once

#ifdef _WIN32
    #ifdef WINDOWING_BUILDING_DLL
        #define WINDOWING_API __declspec(dllexport)
    #else
        #define WINDOWING_API __declspec(dllimport)
    #endif
#else
    #define WINDOWING_API
#endif
