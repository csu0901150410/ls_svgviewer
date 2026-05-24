add_library(graphics SHARED)

target_sources(graphics
    PRIVATE
        debug_renderer.cpp
        scene.cpp
)

target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(graphics
    PRIVATE
        GRAPHICS_BUILDING_DLL
)
