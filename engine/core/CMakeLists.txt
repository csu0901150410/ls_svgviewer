add_library(core STATIC)

target_sources(core
    PRIVATE
        logger.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

message("core include dir : ${CMAKE_CURRENT_SOURCE_DIR}")
