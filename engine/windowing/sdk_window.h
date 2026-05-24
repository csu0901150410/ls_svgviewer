#pragma once

#include "native_window.h"
#include "windowing_api.h"

namespace windowing
{
    class WINDOWING_API sdk_window
    {
    public:
        sdk_window();
        ~sdk_window();

        sdk_window(const sdk_window&) = delete;
        sdk_window& operator=(const sdk_window&) = delete;

        sdk_window(sdk_window&& other) noexcept;
        sdk_window& operator=(sdk_window&& other) noexcept;

        bool create(const char* title, int width, int height);
        void show();
        void close();
        void poll_events();

        bool should_close() const;
        int width() const;
        int height() const;
        graphics::native_window_handle native_handle() const;

    private:
        void* handle = nullptr;
        bool closeRequested = false;
        int clientWidth = 0;
        int clientHeight = 0;
    };
}
