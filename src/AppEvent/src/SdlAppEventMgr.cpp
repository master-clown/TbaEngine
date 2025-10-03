#include <AppEvent/SdlAppEventMgr.h>

#include <AppEvent/EventInfo.hpp>

#include <SDL3/SDL_events.h>

//======================================================================================================================
using namespace app_event;

//======================================================================================================================
struct SdlAppEventMgr::Pimpl final {
    SDL_Event sdlEvent;
};

//======================================================================================================================
SdlAppEventMgr::SdlAppEventMgr()
    : _pimpl(makeUPtr<Pimpl>())
{
    SDL_zero(_pimpl->sdlEvent);
}

//======================================================================================================================
SdlAppEventMgr::~SdlAppEventMgr() = default;

//======================================================================================================================
AppEvent SdlAppEventMgr::getNextEvent()
{
    auto& sdlEvent = _pimpl->sdlEvent;

    const auto newEventsAvailable = SDL_PollEvent(&sdlEvent);
    if (!newEventsAvailable)
        return NoneAppEvent{};

    switch (sdlEvent.type) {
    case SDL_EventType::SDL_EVENT_QUIT: return WindowEvent{WindowEventKind::QuitRequested};
    }

    // TODO: add verbose log about missed event (very verbose)

    return NoneAppEvent{};
}
