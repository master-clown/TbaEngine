#include <GuiAppTemplate/GuiAppTemplate.h>

#include <AppEvent/AppEvent.hpp>
#include <Common/Memory.h>
#include <EventInfo/EventInfo.hpp>
#include <Framework/Framework.h>
#include <Winsys/WindowMgr.h>

#include <cassert>

//======================================================================================================================
using gui_app_template::GuiAppTemplate;

//======================================================================================================================
GuiAppTemplate::GuiAppTemplate(winsys::WindowOptions winOpts)
    : framework::RenderableApplication(framework::RefreshRateOptions{})
    , _appWindowOptions(std::move(winOpts))
{
    if (_appWindowOptions.wndWidth == 0)
        _appWindowOptions.wndWidth = 640;

    if (_appWindowOptions.wndHeight == 0)
        _appWindowOptions.wndHeight = 480;
}

//----------------------------------------------------------------------------------------------------------------------
GuiAppTemplate::~GuiAppTemplate() = default;

//======================================================================================================================
void GuiAppTemplate::_init()
{
    _appWindow = _createWindow(_appWindowOptions);
}

//======================================================================================================================
auto GuiAppTemplate::_iterate(const app_event::AppEvent& appEventVariant) -> ShouldQuit
{
    const auto shouldQuit = _processEvent(appEventVariant);

    return shouldQuit;
}

//======================================================================================================================
void GuiAppTemplate::_render()
{
}

//======================================================================================================================
uptr<winsys::Window> GuiAppTemplate::_createWindow(const winsys::WindowOptions& windowOptions)
{
    return getFramework().getWindowMgr().createWindow(windowOptions);
}

//======================================================================================================================
auto GuiAppTemplate::_processEvent(const app_event::AppEvent& appEvent) -> ShouldQuit
{
    if (const auto* windowEvent = appEvent.getIf<win_event::WindowEvent>()) {
        using Kind = win_event::WindowEventKind;
        switch (windowEvent->getKind()) {
        case Kind::QuitRequested: return ShouldQuit{true};
        }
    }

    return ShouldQuit{false};
}

//======================================================================================================================
winsys::Window& GuiAppTemplate::_getWindow()
{
    return const_cast<winsys::Window&>(static_cast<const GuiAppTemplate&>(*this)._getWindow());
}

//======================================================================================================================
const winsys::Window& GuiAppTemplate::_getWindow() const
{
    assert(_appWindow && "Make sure _createWindow() method is indeed called");
    return *_appWindow;
}
