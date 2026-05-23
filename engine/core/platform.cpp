#include <platform.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace core
{
    shared_library::~shared_library()
    {
        // 析构时自动卸载动态库
        unload();
    }

    shared_library::shared_library(shared_library&& other) noexcept
        : handle(other.handle)
    {
        other.handle = nullptr;
    }

    shared_library& shared_library::operator=(shared_library&& other) noexcept
    {
        if (this == &other)
            return *this;

        unload();
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }

    bool shared_library::load(const char* path)
    {
        if (!path)
            return false;

        unload();

        // load dynamic library
#ifdef _WIN32
        handle = (void*)LoadLibraryA(path);
#else
        handle = dlopen(path, RTLD_NOW);
#endif

        if (nullptr == handle)
            return false;
        return true;
    }

    void* shared_library::get_symbol(const char* name)
    {
        if (!handle || !name)
            return nullptr;

#ifdef _WIN32
        return (void*)GetProcAddress((HMODULE)handle, name);
#else
        return dlsym(handle, name);
#endif
    }

    void shared_library::unload()
    {
        if (!handle)
            return;

#ifdef _WIN32
        FreeLibrary((HMODULE)handle);
#else
        dlclose(handle);
#endif

        handle = nullptr;
    }
}
