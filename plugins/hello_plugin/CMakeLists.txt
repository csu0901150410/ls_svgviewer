add_library(hello_plugin SHARED)

target_sources(hello_plugin
    PRIVATE
        hello_plugin.cpp
)

# 插件只依赖core模块的头文件
target_include_directories(hello_plugin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/engine/core
)

# 插件输出到单独的plugins文件夹
set_target_properties(hello_plugin
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/plugins
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/plugins
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>/plugins
)
