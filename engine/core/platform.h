#pragma once

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
