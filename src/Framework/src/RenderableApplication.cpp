#include <Framework/RenderableApplication.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>

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
    auto& appEventMgr = getFramework().getAppEventMgr();
    while (true) {
        _clock._updateCurrentRefreshTicks();

        const auto appEventVariant = appEventMgr.getNextEvent();

        const auto shouldQuit = _iterate(appEventVariant);
        if (shouldQuit)
            break;

        if (_refreshRateLimiter.requestPermissionToRender())
            _render();

        _refreshRateLimiter.wait();
    }
}
