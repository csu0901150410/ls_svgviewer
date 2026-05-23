#include "plugin.h"
#include "plugin_api.h"

class hello_plugin : public core::plugin
{
public:
    const char* name() override
    {
        return "hello_plugin";
    }
};

extern "C"
{
    PLUGIN_API core::plugin* create_plugin()
    {
        return new hello_plugin();
    }

    PLUGIN_API void destroy_plugin(core::plugin* plugin)
    {
        delete plugin;
    }
}
