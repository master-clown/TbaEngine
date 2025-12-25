#include <AppEvent/SdlAppEventMgr.h>

#include <AppEvent/EventInfo.hpp>

#include <Common/Stl/Optional.h>

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
void SdlAppEventMgr::update()
{
    auto& sdlEvent = _pimpl->sdlEvent;

    const auto newEventsAvailable = SDL_PollEvent(&sdlEvent);
    if (!newEventsAvailable)
        return;

    auto newEvent = [&] -> Optional<AppEvent> {
        switch (sdlEvent.type) {
        case SDL_EventType::SDL_EVENT_QUIT: return WindowEvent{WindowEventKind::QuitRequested};
        default: return {};
        }
    }();

    if (!newEvent.has_value())
        return;

    getEventQueue().push(std::move(*newEvent));
}
