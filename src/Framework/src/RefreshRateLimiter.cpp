#include <Framework/RefreshRateLimiter.h>

#include <thread>

//======================================================================================================================
using namespace framework;

//----------------------------------------------------------------------------------------------------------------------
namespace chrono = std::chrono;

//======================================================================================================================
RefreshRateLimiter::RefreshRateLimiter(const Clock& clock, RefreshRateOptions refreshRateOpts)
    : _clock(clock)
    , _refreshRateOptions(std::move(refreshRateOpts))
    , _nsecRefreshSeparation(chrono::duration_cast<NsecsTillNextRefresh>(chrono::seconds(1)) /
                             _refreshRateOptions.maxLogicRefreshRatePerSecond)
{
}

//======================================================================================================================
// TODO: improve sleep time precision (the current algorithm is a naive one)
void RefreshRateLimiter::wait()
{
    const auto currentRealTicks = _clock.getRealTicksSinceStart();
    const auto nextPlannedRefreshTicks = _clock.getCurrentRefreshTicks() + _nsecRefreshSeparation;
    if (nextPlannedRefreshTicks <= currentRealTicks)
        return;

    const auto sleepTime = nextPlannedRefreshTicks - currentRealTicks;
    std::this_thread::sleep_for(sleepTime);
}

//======================================================================================================================
auto RefreshRateLimiter::requestPermissionToRender() -> IsRenderAllowed
{
    if (++_performedLogicUpdatesBeforeRender >= _refreshRateOptions.logicRefreshesPerRenderFrame) {
        _performedLogicUpdatesBeforeRender = 0;
        return IsRenderAllowed{true};
    }

    return IsRenderAllowed{false};
}
