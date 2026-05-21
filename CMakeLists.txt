cmake_minimum_required(VERSION 3.23)

project(svgviewer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# core
add_subdirectory(engine/core)

# plugins
add_subdirectory(plugins/hello_plugin)

# app
add_subdirectory(app)
