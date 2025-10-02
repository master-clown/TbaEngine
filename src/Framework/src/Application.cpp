#include <Framework/Application.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
Application::~Application() = default;

//======================================================================================================================
void Application::run()
{
    auto framework = _init();

    auto& appEventMgr = framework->getAppEventMgr();
    while (true) {
        const auto appEventVariant = appEventMgr.getNextEvent();

        const auto shouldQuit = _iterate(appEventVariant);
        if (shouldQuit)
            break;
    }
}
