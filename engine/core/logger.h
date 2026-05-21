#pragma once

#include "core_api.h"

namespace core
{
    class CORE_API logger
    {
    public:
        static void info(const char* msg);
    };
}
