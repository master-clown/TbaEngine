#pragma once

#include <EventSys/NativeEvent.h>

#include <SDL3/SDL_events.h>

//======================================================================================================================
namespace sdl_event_sys {
    class SdlNativeEvent final : public event_sys::NativeEvent {
    public:
        explicit SdlNativeEvent(SDL_Event);

        String str() const override;

        const SDL_Event& getSdlEvent() const;

    private:
        SDL_Event _sdlEvent;
    };
}
