#include <Framework/RenderableApplication.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
RenderableApplication::RenderableApplication() = default;

//======================================================================================================================
RenderableApplication::~RenderableApplication() = default;

//======================================================================================================================
void RenderableApplication::_run()
{
    auto& appEventMgr = getFramework().getAppEventMgr();
    while (true) {
        const auto appEventVariant = appEventMgr.getNextEvent();

        const auto shouldQuit = _iterate(appEventVariant);
        if (shouldQuit)
            break;
    }
}
