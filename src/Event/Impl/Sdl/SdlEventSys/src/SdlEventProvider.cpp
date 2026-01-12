#include <SdlEventSys/SdlEventProvider.h>

#include <SdlEventSys/SdlNativeEvent.h>

#include <SDL3/SDL_events.h>

//======================================================================================================================
using namespace sdl_event_sys;

//======================================================================================================================
Vector<uptr<event_sys::NativeEvent>> SdlEventProvider::fetchNewNativeEvents()
{
    Vector<uptr<event_sys::NativeEvent>> nativeEvents;

    SDL_Event sdlEvent;
    SDL_zero(sdlEvent);

    while (const auto newEventsAvailable = SDL_PollEvent(&sdlEvent))
        nativeEvents.emplace_back(makeUPtr<SdlNativeEvent>(sdlEvent));

    return nativeEvents;
}
