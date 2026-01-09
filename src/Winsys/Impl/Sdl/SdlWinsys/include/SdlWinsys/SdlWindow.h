#pragma once

#include <AppEvent/NativeEventListener.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace app_event {
    class NativeEventListeners;
}

//======================================================================================================================
struct SDL_Window;

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow final : public winsys::Window,
                            public app_event::NativeEventListener {
    public:
        SdlWindow(app_event::NativeEventListeners&, winsys::WindowOptions);
        ~SdlWindow();

        Optional<app_event::AppEvent> transformToAppEvent(const app_event::NativeEvent&) override;

        //--------------------------------------------------------------------------------------------------------------
        SDL_Window& getRawWindow();
        const SDL_Window& getRawWindow() const;

    private:
        SDL_Window* _sdlWindow = nullptr;
    };
}
