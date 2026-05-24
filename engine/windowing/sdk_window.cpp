#include "sdk_window.h"

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#endif

namespace
{
#ifdef _WIN32
    constexpr const char* window_class_name = "LsGraphicsSdkWindow";

    graphics::key_modifiers current_modifiers()
    {
        return {
            (GetKeyState(VK_CONTROL) & 0x8000) != 0,
            (GetKeyState(VK_SHIFT) & 0x8000) != 0,
            (GetKeyState(VK_MENU) & 0x8000) != 0};
    }

    void dispatch_input_event(windowing::sdk_window* window, const graphics::input_event& event)
    {
        if (window)
            window->dispatch_input_event(event);
    }

    LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        auto* window = reinterpret_cast<windowing::sdk_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (message == WM_NCCREATE)
        {
            const auto* createStruct = reinterpret_cast<CREATESTRUCTA*>(lparam);
            window = reinterpret_cast<windowing::sdk_window*>(createStruct->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        }

        switch (message)
        {
        case WM_CLOSE:
            if (window)
                window->close();
            return 0;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        {
            if (window)
                SetCapture(hwnd);

            graphics::input_event event;
            event.type = graphics::input_event_type::mouse_down;
            event.position = {static_cast<float>(GET_X_LPARAM(lparam)), static_cast<float>(GET_Y_LPARAM(lparam))};
            event.modifiers = current_modifiers();
            event.button = message == WM_LBUTTONDOWN
                ? graphics::mouse_button::left
                : message == WM_MBUTTONDOWN ? graphics::mouse_button::middle : graphics::mouse_button::right;
            dispatch_input_event(window, event);
            return 0;
        }
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        {
            ReleaseCapture();

            graphics::input_event event;
            event.type = graphics::input_event_type::mouse_up;
            event.position = {static_cast<float>(GET_X_LPARAM(lparam)), static_cast<float>(GET_Y_LPARAM(lparam))};
            event.modifiers = current_modifiers();
            event.button = message == WM_LBUTTONUP
                ? graphics::mouse_button::left
                : message == WM_MBUTTONUP ? graphics::mouse_button::middle : graphics::mouse_button::right;
            dispatch_input_event(window, event);
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            graphics::input_event event;
            event.type = graphics::input_event_type::mouse_move;
            event.position = {static_cast<float>(GET_X_LPARAM(lparam)), static_cast<float>(GET_Y_LPARAM(lparam))};
            event.modifiers = current_modifiers();
            dispatch_input_event(window, event);
            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            POINT point{GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)};
            ScreenToClient(hwnd, &point);

            graphics::input_event event;
            event.type = graphics::input_event_type::mouse_wheel;
            event.position = {static_cast<float>(point.x), static_cast<float>(point.y)};
            event.wheel_delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wparam)) / static_cast<float>(WHEEL_DELTA);
            event.modifiers = current_modifiers();
            dispatch_input_event(window, event);
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            graphics::input_event event;
            event.type = graphics::input_event_type::key_down;
            event.key = static_cast<int>(wparam);
            event.modifiers = current_modifiers();
            dispatch_input_event(window, event);
            return 0;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            graphics::input_event event;
            event.type = graphics::input_event_type::key_up;
            event.key = static_cast<int>(wparam);
            event.modifiers = current_modifiers();
            dispatch_input_event(window, event);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }

    bool register_window_class()
    {
        static bool registered = false;
        if (registered)
            return true;

        WNDCLASSEXA windowClass{};
        windowClass.cbSize = sizeof(windowClass);
        windowClass.lpfnWndProc = window_proc;
        windowClass.hInstance = GetModuleHandleA(nullptr);
        windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        windowClass.lpszClassName = window_class_name;

        registered = RegisterClassExA(&windowClass) != 0;
        return registered;
    }
#endif
}

namespace windowing
{
    sdk_window::sdk_window() = default;

    sdk_window::~sdk_window()
    {
        close();
    }

    sdk_window::sdk_window(sdk_window&& other) noexcept
        : handle(other.handle),
          closeRequested(other.closeRequested),
          clientWidth(other.clientWidth),
          clientHeight(other.clientHeight)
    {
        other.handle = nullptr;
        other.closeRequested = true;
        other.clientWidth = 0;
        other.clientHeight = 0;
    }

    sdk_window& sdk_window::operator=(sdk_window&& other) noexcept
    {
        if (this == &other)
            return *this;

        close();
        handle = other.handle;
        closeRequested = other.closeRequested;
        clientWidth = other.clientWidth;
        clientHeight = other.clientHeight;

        other.handle = nullptr;
        other.closeRequested = true;
        other.clientWidth = 0;
        other.clientHeight = 0;
        return *this;
    }

    bool sdk_window::create(const char* title, int width, int height)
    {
        close();

        if (!title || width <= 0 || height <= 0)
            return false;

#ifdef _WIN32
        if (!register_window_class())
            return false;

        RECT rect{0, 0, width, height};
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        handle = CreateWindowExA(
            0,
            window_class_name,
            title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            nullptr,
            nullptr,
            GetModuleHandleA(nullptr),
            this);

        if (!handle)
            return false;

        closeRequested = false;
        clientWidth = width;
        clientHeight = height;
        return true;
#else
        (void)title;
        (void)width;
        (void)height;
        return false;
#endif
    }

    void sdk_window::show()
    {
#ifdef _WIN32
        if (handle)
            ShowWindow(static_cast<HWND>(handle), SW_SHOW);
#endif
    }

    void sdk_window::close()
    {
#ifdef _WIN32
        if (handle)
        {
            DestroyWindow(static_cast<HWND>(handle));
            handle = nullptr;
        }
#endif
        closeRequested = true;
        clientWidth = 0;
        clientHeight = 0;
    }

    void sdk_window::poll_events()
    {
#ifdef _WIN32
        MSG message{};
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
#endif
    }

    void sdk_window::set_input_event_callback(input_event_callback callback, void* userData)
    {
        inputCallback = callback;
        inputUserData = userData;
    }

    void sdk_window::dispatch_input_event(const graphics::input_event& event)
    {
        if (inputCallback)
            inputCallback(event, inputUserData);
    }

    bool sdk_window::should_close() const
    {
        return closeRequested;
    }

    int sdk_window::width() const
    {
        return clientWidth;
    }

    int sdk_window::height() const
    {
        return clientHeight;
    }

    graphics::native_window_handle sdk_window::native_handle() const
    {
        return handle;
    }
}
