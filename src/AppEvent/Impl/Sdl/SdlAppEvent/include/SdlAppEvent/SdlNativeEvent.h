#pragma once

#include <AppEvent/NativeEvent.h>

#include <SDL3/SDL_events.h>

//======================================================================================================================
namespace app_event {
    class SdlNativeEvent final : public NativeEvent {
    public:
        explicit SdlNativeEvent(SDL_Event);

        String str() const override;

        const SDL_Event& getSdlEvent() const;

    private:
        SDL_Event _sdlEvent;
    };
}
