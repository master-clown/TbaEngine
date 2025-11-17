#include <Framework/SdlFramework.h>

#include <AppEvent/SdlAppEventMgr.h>
#include <SdlRenderer/SdlRenderer.h>
#include <Winsys/SdlWindowMgr.h>

#include <SDL3/SDL.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
using framework::SdlFramework;

//======================================================================================================================
SdlFramework::SdlFramework()
    : _sdlLibraryRaiiWrapper{}
    , _sdlWinMgr(makeUPtr<winsys::SdlWindowMgr>())
    , _sdlAppEventMgr(makeUPtr<app_event::SdlAppEventMgr>())
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
uptr<render::Renderer> SdlFramework::createRenderer(const render::RendererType renderType)
{
    using Type = render::RendererType;

    switch (renderType) {
    case Type::Sdl: return makeUPtr<sdl_render::SdlRenderer>();
    default: break;
    }

    throw std::runtime_error("Unsupported renderer type is passed: " + str(renderType));
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
