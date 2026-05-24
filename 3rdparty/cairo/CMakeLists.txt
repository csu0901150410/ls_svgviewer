add_library(cairo SHARED IMPORTED GLOBAL)

# 根据指针位数确定x64还是x86
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CAIRO_ARCH_DIR x64)
else()
    set(CAIRO_ARCH_DIR x86)
endif()

set_target_properties(cairo PROPERTIES
    # 编译期导入库
    IMPORTED_IMPLIB
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CAIRO_ARCH_DIR}/cairo.lib

    # 运行时动态库
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CAIRO_ARCH_DIR}/cairo.dll

    # 头文件
    INTERFACE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
