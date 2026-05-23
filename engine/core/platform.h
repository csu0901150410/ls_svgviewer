#pragma once

/**
 * 平台相关层，具体功能在各平台的实现
 */

namespace core
{
    class shared_library
    {
    public:
        shared_library() = default;
        ~shared_library();

        // 禁用复制构造函数
        shared_library(const shared_library&) = delete;
        // 禁用赋值运算符
        shared_library& operator=(const shared_library&) = delete;

        // 移动构造函数
        shared_library(shared_library&& other) noexcept;
        // 移动赋值运算符
        shared_library& operator=(shared_library&& other) noexcept;

        bool load(const char* path);

        void* get_symbol(const char* name);

        void unload();

    private:
        void* handle = nullptr;
    };
}
