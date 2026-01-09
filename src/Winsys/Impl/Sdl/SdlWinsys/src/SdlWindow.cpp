#include <SdlWinsys/SdlWindow.h>

#include <AppEvent/EventInfo.hpp>
#include <AppEvent/NativeEventListeners.h>
#include <SdlAppEvent/SdlNativeEvent.h>

#include <SDL3/SDL_video.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
using namespace sdl_winsys;
using namespace winsys;

//======================================================================================================================
SdlWindow::SdlWindow(app_event::NativeEventListeners& nativeEventListeners, WindowOptions optionsArg)
    : winsys::Window(std::move(optionsArg))
    , app_event::NativeEventListener(nativeEventListeners)
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
Optional<app_event::AppEvent> SdlWindow::transformToAppEvent(const app_event::NativeEvent& nativeEvent)
{
    assert(dynamic_cast<const sdl_app_event::SdlNativeEvent*>(&nativeEvent));

    const auto& sdlNativeEvent = static_cast<const sdl_app_event::SdlNativeEvent&>(nativeEvent);
    const auto& sdlEvent = sdlNativeEvent.getSdlEvent();

    switch (sdlEvent.type) {
    case SDL_EventType::SDL_EVENT_QUIT: return app_event::WindowEvent{app_event::WindowEventKind::QuitRequested};
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
