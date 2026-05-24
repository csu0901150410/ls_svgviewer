add_library(windowing SHARED)

target_sources(windowing
    PRIVATE
        sdk_window.cpp
)

target_include_directories(windowing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(windowing
    PUBLIC
        graphics
)

target_compile_definitions(windowing
    PRIVATE
        WINDOWING_BUILDING_DLL
)

if(WIN32)
    target_link_libraries(windowing
        PRIVATE
            user32
    )
endif()
