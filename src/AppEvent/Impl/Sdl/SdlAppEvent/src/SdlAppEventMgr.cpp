#include <SdlAppEvent/SdlAppEventMgr.h>

#include <SdlAppEvent/SdlNativeEvent.h>

#include <SDL3/SDL_events.h>

//======================================================================================================================
using namespace sdl_app_event;

//======================================================================================================================
Vector<uptr<app_event::NativeEvent>> SdlAppEventMgr::_fetchNativeEvents()
{
    Vector<uptr<app_event::NativeEvent>> nativeEvents;

    SDL_Event sdlEvent;
    SDL_zero(sdlEvent);

    while (const auto newEventsAvailable = SDL_PollEvent(&sdlEvent))
        nativeEvents.emplace_back(makeUPtr<SdlNativeEvent>(sdlEvent));

    return nativeEvents;
}
