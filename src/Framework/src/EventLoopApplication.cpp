#include <Framework/EventLoopApplication.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
EventLoopApplication::EventLoopApplication() = default;

//======================================================================================================================
EventLoopApplication::~EventLoopApplication() = default;

//======================================================================================================================
void EventLoopApplication::run()
{
    _framework = _init();

    auto& appEventMgr = _framework->getAppEventMgr();
    while (true) {
        const auto appEventVariant = appEventMgr.getNextEvent();

        const auto shouldQuit = _iterate(appEventVariant);
        if (shouldQuit)
            break;
    }
}
