#pragma once

/**
 * 平台相关层，具体功能在各平台的实现
 */

namespace core
{
    class shared_library
    {
    public:
        bool load(const char* path);

        void* get_symbol(const char* name);

        void unload();

    private:
        void* handle = nullptr;
    };
}
