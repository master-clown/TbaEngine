#include "GuiTest.h"

#include <AppEvent/EventInfo.hpp>
#include <Common/Memory.h>
#include <Framework/SdlFramework.h>
#include <Winsys/WindowMgr.h>

//======================================================================================================================
uptr<framework::Framework> GuiTest::_init()
{
    auto fr = makeUPtr<framework::SdlFramework>();
    _appWindow = fr->getWindowMgr().createWindow(winsys::WindowOptions{
        .wndTitle = "Hello!",
        .wndWidth = 640,
        .wndHeight = 480,
    });

    return fr;
}

//======================================================================================================================
auto GuiTest::_iterate(const app_event::AppEvent& appEventVariant) -> ShouldQuit
{
    if (const auto* windowEvent = std::get_if<app_event::WindowEvent>(&appEventVariant)) {
        using Kind = app_event::WindowEventKind;
        switch (windowEvent->getKind()) {
        case Kind::QuitRequested: return ShouldQuit{true};
        }
    }

    return ShouldQuit{false};
}
