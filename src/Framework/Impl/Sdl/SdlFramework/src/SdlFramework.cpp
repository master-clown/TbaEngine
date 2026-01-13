#include <SdlFramework/SdlFramework.h>

#include <EventSys/EventMgr.h>
#include <SdlEventSys/SdlEventProvider.h>
#include <SdlRenderer/SdlRenderer.h>
#include <SdlWinsys/SdlWindow.h>
#include <SdlWinsys/SdlWindowMgr.h>

#include <SDL3/SDL.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
using sdl_framework::SdlFramework;

//======================================================================================================================
SdlFramework::SdlFramework()
    : _sdlLibraryRaiiWrapper{}
    , _sdlEventMgr(makeUPtr<event_sys::EventMgr>(makeUPtr<sdl_event_sys::SdlEventProvider>()))
    , _sdlWinMgr(makeUPtr<sdl_winsys::SdlWindowMgr>(_sdlEventMgr->getNativeEventListeners()))
{
}

//----------------------------------------------------------------------------------------------------------------------
SdlFramework::~SdlFramework() = default;

//======================================================================================================================
event_sys::EventMgr& SdlFramework::getEventMgr()
{
    assert(_sdlEventMgr);
    return *_sdlEventMgr;
}

//----------------------------------------------------------------------------------------------------------------------
winsys::WindowMgr& SdlFramework::getWindowMgr()
{
    assert(_sdlWinMgr);
    return *_sdlWinMgr;
}

//----------------------------------------------------------------------------------------------------------------------
uptr<render::Renderer> SdlFramework::createRenderer(const render::RendererType renderType,
                                                    TargetWindow& targetWindow)
{
    using Type = render::RendererType;

    switch (renderType) {
    case Type::Sdl: return SdlFramework::_createSdlRenderer(targetWindow);
    default: break;
    }

    throw std::runtime_error("Unsupported renderer type is passed: " + str(renderType));
}

//======================================================================================================================
uptr<render::Renderer> SdlFramework::_createSdlRenderer(TargetWindow& targetWindow)
{
    auto* sdlWindow = dynamic_cast<sdl_winsys::SdlWindow*>(&targetWindow);
    if (!sdlWindow)
        throw std::runtime_error("SdlRenderer can be created only for target window of type 'SdlWindow'");

    return makeUPtr<sdl_render::SdlRenderer>(*sdlWindow);
}

//======================================================================================================================
SdlFramework::SdlLibraryRaiiWrapper::SdlLibraryRaiiWrapper()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error("SDL could not initialize! SDL error: " + std::string{SDL_GetError()});
}

//======================================================================================================================
SdlFramework::SdlLibraryRaiiWrapper::~SdlLibraryRaiiWrapper()
{
    SDL_Quit();
}
