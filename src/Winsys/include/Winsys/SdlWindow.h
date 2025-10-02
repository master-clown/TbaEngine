#pragma once

#include <Winsys/Window.h>

//======================================================================================================================
struct SDL_Window;

//======================================================================================================================
namespace winsys {
    class SdlWindow final : public Window {
        using Super = Window;

    public:
        explicit SdlWindow(WindowOptions);
        ~SdlWindow();

        SDL_Window& getRawWindow();
        const SDL_Window& getRawWindow() const;

    private:
        SDL_Window* _sdlWindow = nullptr;
    };
}
