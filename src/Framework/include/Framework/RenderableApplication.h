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

    protected:
        using ShouldQuit = bool;

    private:
        virtual ShouldQuit _iterate(const app_event::AppEvent&) = 0;
        virtual void _render() = 0;

        //--------------------------------------------------------------------------------------------------------------
        void _run() override final;
    };
}
