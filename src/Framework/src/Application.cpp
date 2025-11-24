#include <Framework/Application.h>

#include <Framework/Framework.h>

#include <AppEvent/AppEventMgr.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
Application::Application() = default;

//======================================================================================================================
Application::~Application() = default;

//======================================================================================================================
void Application::run()
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
