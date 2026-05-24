
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# app隐式链接core.dll
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        core
        graphics
        windowing
)
