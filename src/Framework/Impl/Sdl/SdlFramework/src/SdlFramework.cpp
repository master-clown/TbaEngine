#include <SdlFramework/SdlFramework.h>

#include <SdlAppEvent/SdlAppEventMgr.h>
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
    , _sdlAppEventMgr(makeUPtr<sdl_app_event::SdlAppEventMgr>())
    , _sdlWinMgr(makeUPtr<sdl_winsys::SdlWindowMgr>(_sdlAppEventMgr->getNativeEventListeners()))
{
}

//----------------------------------------------------------------------------------------------------------------------
SdlFramework::~SdlFramework() = default;

//======================================================================================================================
winsys::WindowMgr& SdlFramework::getWindowMgr()
{
    assert(_sdlWinMgr);
    return *_sdlWinMgr;
}

//----------------------------------------------------------------------------------------------------------------------
app_event::AppEventMgr& SdlFramework::getAppEventMgr()
{
    assert(_sdlAppEventMgr);
    return *_sdlAppEventMgr;
}

//----------------------------------------------------------------------------------------------------------------------
audio::AudioMgr& SdlFramework::getAudioMgr()
{
    throw std::logic_error("Not implemented");
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
