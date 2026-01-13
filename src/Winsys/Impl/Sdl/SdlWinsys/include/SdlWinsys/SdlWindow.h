#pragma once

#include <EventSys/NativeEventListener.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
struct SDL_Window;

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow final : public winsys::Window,
                            public event_sys::NativeEventListener {
    public:
        SdlWindow(event_sys::NativeEventListeners&, winsys::WindowOptions);
        ~SdlWindow();

        Optional<app_event::AppEvent> transformToAppEvent(const event_sys::NativeEvent&) override;

        //--------------------------------------------------------------------------------------------------------------
        SDL_Window& getRawWindow();
        const SDL_Window& getRawWindow() const;

    private:
        SDL_Window* _sdlWindow = nullptr;
    };
}
