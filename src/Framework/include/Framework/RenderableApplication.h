#pragma once

#include <Framework/Application.h>

#include <AppEvent/AppEvent.h> // TODO: avoid this include (not very light)
#include <Common/Memory.h>

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    class Framework;

    //==================================================================================================================
    class RenderableApplication : public Application {
    public:
        RenderableApplication();
        ~RenderableApplication();

        void run() override final;

    protected:
        using ShouldQuit = bool;

    private:
        virtual uptr<Framework> _init() = 0;
        virtual ShouldQuit _iterate(const app_event::AppEvent&) = 0;

    private:
        uptr<Framework> _framework;
    };
}
