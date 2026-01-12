#include <Framework/RenderableApplication.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEvent.h>
#include <EventSys/EventMgr.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
RenderableApplication::RenderableApplication(RefreshRateOptions refreshRateOpts)
    : _refreshRateLimiter(_clock, std::move(refreshRateOpts))
{
}

//======================================================================================================================
RenderableApplication::~RenderableApplication() = default;

//======================================================================================================================
void RenderableApplication::_run()
{
    auto& eventMgr = getFramework().getEventMgr();
    while (true) {
        _clock._updateCurrentRefreshTicks();
        eventMgr.pollEvents();

        const auto appEventVariant = eventMgr.getNextEvent();

        const auto shouldQuit = _iterate(appEventVariant);
        if (shouldQuit)
            break;

        if (_refreshRateLimiter.requestPermissionToRender())
            _render();

        _refreshRateLimiter.wait();
    }
}
