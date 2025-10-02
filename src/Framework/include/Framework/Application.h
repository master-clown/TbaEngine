#pragma once

#include <AppEvent/AppEvent.h> // TODO: avoid this include (not very light)
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

    protected:
        using ShouldQuit = bool;

    private:
        virtual uptr<Framework> _init() = 0;
        virtual ShouldQuit _iterate(const app_event::AppEvent&) = 0;
    };
}
