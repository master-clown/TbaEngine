#include <SdlWinsys/SdlWindow.h>

#include <AppEvent/AppEvent.h>
#include <EventInfo/EventInfo.hpp>
#include <EventSys/NativeEventListeners.h>
#include <SdlEventSys/SdlNativeEvent.h>

#include <SDL3/SDL_video.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
using namespace sdl_winsys;
using namespace winsys;

//======================================================================================================================
SdlWindow::SdlWindow(event_sys::NativeEventListeners& nativeEventListeners, WindowOptions optionsArg)
    : winsys::Window(std::move(optionsArg))
    , event_sys::NativeEventListener(nativeEventListeners)
{
    const WindowOptions& options = getWindowOptions();

    _sdlWindow = SDL_CreateWindow(options.wndTitle.c_str(),
                                  options.wndWidth,
                                  options.wndHeight,
                                  0);

    if (!_sdlWindow)
        throw std::runtime_error("Cannot create window (title=" + options.wndTitle + "): " + SDL_GetError());
}

//----------------------------------------------------------------------------------------------------------------------
SdlWindow::~SdlWindow()
{
    SDL_DestroyWindow(_sdlWindow);
}

//======================================================================================================================
Optional<app_event::AppEvent> SdlWindow::transformToAppEvent(const event_sys::NativeEvent& nativeEvent)
{
    assert(dynamic_cast<const sdl_event_sys::SdlNativeEvent*>(&nativeEvent));

    const auto& sdlNativeEvent = static_cast<const sdl_event_sys::SdlNativeEvent&>(nativeEvent);
    const auto& sdlEvent = sdlNativeEvent.getSdlEvent();

    switch (sdlEvent.type) {
    case SDL_EventType::SDL_EVENT_QUIT:
        return app_event::AppEvent{win_event::WindowEvent{win_event::WindowEventKind::QuitRequested}};
    default: return std::nullopt;
    }
}

//======================================================================================================================
SDL_Window& SdlWindow::getRawWindow()
{
    return *_sdlWindow;
}

//----------------------------------------------------------------------------------------------------------------------
const SDL_Window& SdlWindow::getRawWindow() const
{
    return *_sdlWindow;
}
