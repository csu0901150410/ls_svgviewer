#pragma once

namespace core
{
    class plugin
    {
    public:
        virtual ~plugin() = default;

        virtual const char* name() = 0;
    };
}
