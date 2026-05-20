#include "logger.h"

#include <iostream>

namespace core
{
    void logger::info(const char* msg)
    {
        std::cout << "[INFO] " << msg << std::endl;
    }
}
