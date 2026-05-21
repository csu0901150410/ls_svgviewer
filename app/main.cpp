#include <iostream>

#include "logger.h"
#include "plugin_manager.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    core::logger::info("Hello, World!");

    core::plugin_manager manager;
    manager.load_plugin("plugins/hello_plugin.dll");

    return 0;
}
