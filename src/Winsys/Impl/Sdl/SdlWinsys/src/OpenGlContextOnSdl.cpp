#include "OpenGlContextOnSdl.h"

#include <SdlWinsys/SdlWindow.h>

#include <SDL3/SDL_video.h>

#include <cassert>
#include <stdexcept>

//======================================================================================================================
using sdl_winsys::OpenGlContextOnSdl;

//======================================================================================================================
struct OpenGlContextOnSdl::_Pimpl final {
    SDL_GLContext context = nullptr;
};

//======================================================================================================================
OpenGlContextOnSdl::OpenGlContextOnSdl()
    : _pimpl(makeUPtr<_Pimpl>())
{
}

//======================================================================================================================
OpenGlContextOnSdl::~OpenGlContextOnSdl() = default;

//======================================================================================================================
void OpenGlContextOnSdl::initContext(winsys::Window& targetWindow)
{
    assert(dynamic_cast<SdlWindow*>(&targetWindow));

    _sdlWindow = static_cast<SdlWindow*>(&targetWindow);
    _pimpl->context = SDL_GL_CreateContext(&_sdlWindow->getRawWindow());
    if (!_pimpl->context)
        throw std::runtime_error(String("Failed to init OpenGL context on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::freeContext()
{
    assert(_pimpl->context);
    if (!SDL_GL_DestroyContext(_pimpl->context))
        throw std::runtime_error(String("Failed to free OpenGL context on SDL framework: ") + SDL_GetError());

    _pimpl->context = nullptr;
    _sdlWindow = nullptr;
}

//======================================================================================================================
void OpenGlContextOnSdl::makeGlContextAsCurrent()
{
    assert(_pimpl->context);
    assert(_sdlWindow);
    if (!SDL_GL_MakeCurrent(&_sdlWindow->getRawWindow(), _pimpl->context))
        throw std::runtime_error(String("Failed to set OpenGL context as current on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::setSwapInterval(int value)
{
    assert(_pimpl->context);
    if (!SDL_GL_SetSwapInterval(value))
        throw std::runtime_error(String("Failed to set OpenGL swap interval on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::swapBuffers()
{
    assert(_pimpl->context);
    assert(_sdlWindow);
    if (!SDL_GL_SwapWindow(&_sdlWindow->getRawWindow()))
        throw std::runtime_error(String("Failed to swap OpenGL buffers on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::setGlMajorVersion(uint32 majorValue)
{
    assert(_pimpl->context);
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorValue))
        throw std::runtime_error(
            String("Failed to set OpenGL major version attrib on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::setGlMinorVersion(uint32 minorValue)
{
    assert(_pimpl->context);
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorValue))
        throw std::runtime_error(
            String("Failed to set OpenGL minor version attrib on SDL framework: ") + SDL_GetError());
}

//======================================================================================================================
void OpenGlContextOnSdl::setGlProfile(GlProfile glProfile)
{
    assert(_pimpl->context);
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                             glProfile == GlProfile::Core ? SDL_GL_CONTEXT_PROFILE_CORE
                                                          : SDL_GL_CONTEXT_PROFILE_COMPATIBILITY))
        throw std::runtime_error(String("Failed to set OpenGL profile attrib on SDL framework: ") + SDL_GetError());
}
