#include "plugin.h"
#include "logger.h"

class hello_plugin : public core::plugin
{
public:
    const char* name() override
    {
        return "hello_plugin";
    }
};

// 导出工厂函数
extern "C"
{
    __declspec(dllexport) core::plugin* create_plugin()
    {
        return new hello_plugin();
    }
}
