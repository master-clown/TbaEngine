#pragma once

#include <Framework/Application.h>
#include <Framework/Clock.h>
#include <Framework/RefreshRateLimiter.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace app_event {
    class AppEvent;
}

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    class RenderableApplication : public Application {
    public:
        explicit RenderableApplication(RefreshRateOptions);
        ~RenderableApplication();

    protected:
        using ShouldQuit = bool;

    private:
        virtual ShouldQuit _iterate(const app_event::AppEvent&) = 0;
        virtual void _render() = 0;

        //--------------------------------------------------------------------------------------------------------------
        void _run() override final;

    private:
        Clock _clock;
        RefreshRateLimiter _refreshRateLimiter;
    };
}
