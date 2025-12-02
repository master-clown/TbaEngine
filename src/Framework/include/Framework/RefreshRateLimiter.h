#pragma once

#include <Framework/Clock.h>
#include <Framework/RefreshRateOptions.h>

//======================================================================================================================
namespace framework {
    //==================================================================================================================
    class RefreshRateLimiter final {
    public:
        RefreshRateLimiter(const Clock&, RefreshRateOptions);

        void wait();

        using IsRenderAllowed = bool;
        IsRenderAllowed requestPermissionToRender() const;

    private:
        const Clock& _clock;
        RefreshRateOptions _refreshRateOptions;

        //--------------------------------------------------------------------------------------------------------------
        using NsecsTillNextRefresh = Clock::Nanoseconds;
        NsecsTillNextRefresh _nsecRefreshSeparation;
        mutable uint16 _performedLogicUpdatesBeforeRender = 0;
    };
}
