#include <platform.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace core
{
    bool shared_library::load(const char* path)
    {
        if (!path)
            return false;

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
