#include <chrono>
#include <memory>
#include <thread>

#include "gdi_renderer.h"
#include "logger.h"
#include "primitive.h"
#include "render_target.h"
#include "scene.h"
#include "sdk_window.h"
#include "view.h"

namespace
{
    void forward_input_to_view(const graphics::input_event& event, void* userData)
    {
        auto* view = static_cast<graphics::view*>(userData);
        if (view)
            view->handle_event(event);
    }
}

int main()
{
    core::logger::info("Graphics SDK demo started");

    windowing::sdk_window window;
    if (!window.create("Graphics SDK Demo", 800, 600))
    {
        core::logger::info("Failed to create SDK window");
        return 1;
    }
    window.show();

    graphics::view view;
    window.set_input_event_callback(forward_input_to_view, &view);
    window.poll_events();

    graphics::scene scene;

    scene.add(std::make_unique<graphics::line_primitive>(
        graphics::point{10.0f, 10.0f},
        graphics::point{160.0f, 90.0f},
        graphics::stroke_style{graphics::color::rgba(0.9f, 0.1f, 0.1f), 2.0f}));

    scene.add(std::make_unique<graphics::rect_primitive>(
        graphics::rect{30.0f, 40.0f, 120.0f, 80.0f},
        graphics::fill_style{graphics::color::rgba(0.1f, 0.5f, 0.9f, 0.7f)},
        graphics::stroke_style{graphics::color::rgba(0.0f, 0.0f, 0.0f), 1.5f}));

    scene.add(std::make_unique<graphics::ellipse_primitive>(
        graphics::point{220.0f, 100.0f},
        graphics::size{48.0f, 28.0f},
        graphics::fill_style{graphics::color::rgba(0.2f, 0.8f, 0.3f, 0.8f)},
        graphics::stroke_style{graphics::color::rgba(0.0f, 0.2f, 0.1f), 2.0f}));

    graphics::gdi_renderer renderer;
    const graphics::render_target_desc target{
        window.native_handle(),
        window.width(),
        window.height()};

    if (!renderer.attach(target))
    {
        core::logger::info("Failed to attach render target");
        return 1;
    }

    while (!window.should_close())
    {
        window.poll_events();

        renderer.begin_frame();
        renderer.render(scene);
        renderer.end_frame();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
