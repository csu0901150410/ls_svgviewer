#include <filesystem>
#include <iostream>

#include "logger.h"
#include "plugin_manager.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;

    core::logger::info("Hello, World!");

    const auto executablePath = argc > 0
        ? std::filesystem::absolute(argv[0])
        : std::filesystem::current_path();
    const auto executableDir = executablePath.parent_path();

#ifdef _WIN32
    const auto pluginPath = executableDir / "plugins" / "hello_plugin.dll";
#else
    const auto pluginPath = executableDir / "plugins" / "libhello_plugin.so";
#endif

    auto& manager = core::plugin_manager::instance();
    manager.load_plugin(pluginPath.string().c_str());

    return 0;
}
