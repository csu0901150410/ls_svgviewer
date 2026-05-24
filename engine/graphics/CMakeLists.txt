add_library(graphics SHARED)

target_sources(graphics
    PRIVATE
        debug_renderer.cpp
        gdi_renderer.cpp
        scene.cpp
        view.cpp
)

target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(graphics
    PRIVATE
        GRAPHICS_BUILDING_DLL
)

if(WIN32)
    target_link_libraries(graphics
        PRIVATE
            gdi32
            user32
    )
endif()
