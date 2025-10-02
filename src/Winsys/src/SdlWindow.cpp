#include <Winsys/SdlWindow.h>

#include <SDL3/SDL_video.h>

#include <stdexcept>

//======================================================================================================================
using namespace winsys;

//======================================================================================================================
SdlWindow::SdlWindow(WindowOptions optionsArg)
    : Super(std::move(optionsArg))
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
SDL_Window& SdlWindow::getRawWindow()
{
    return *_sdlWindow;
}

//----------------------------------------------------------------------------------------------------------------------
const SDL_Window& SdlWindow::getRawWindow() const
{
    return *_sdlWindow;
}
