#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    class Framework;

    //==================================================================================================================
    class Application {
    public:
        virtual ~Application();

        void run();

        //--------------------------------------------------------------------------------------------------------------
        Framework& getFramework();
        const Framework& getFramework() const;

    private:
        virtual uptr<Framework> _createFramework() = 0;
        virtual void _init() = 0;
        virtual void _run() = 0;

    private:
        uptr<Framework> _framework;
    };
}
