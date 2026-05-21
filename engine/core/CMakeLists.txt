add_library(core SHARED)

target_sources(core
    PRIVATE
        logger.cpp
        plugin_manager.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 指定编译dll
target_compile_definitions(core
    PRIVATE
        CORE_BUILDING_DLL
)

message("core include dir : ${CMAKE_CURRENT_SOURCE_DIR}")
