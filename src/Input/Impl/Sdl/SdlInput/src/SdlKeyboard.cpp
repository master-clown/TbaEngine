#include <SdlInput/SdlKeyboard.h>

#include "SdlKeyCode.h"
#include "SdlKeyMods.h"
#include "SdlKeyScancode.h"
#include "SdlKeyboardState.h"

#include <AppEvent/AppEvent.h>
#include <EventInfo/EventInfo.hpp>
#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>
#include <SdlEventSys/SdlNativeEvent.h>

#include <cassert>

using namespace sdl_input;

//======================================================================================================================
SdlKeyboard::SdlKeyboard(event_sys::NativeEventListeners& nativeEventListeners)
    : input::Keyboard({.type = input::DeviceType::Keyboard, .publicName = "SDL default keyboard"})
    , event_sys::NativeEventListener(nativeEventListeners)
    , _keyboardState(makeUPtr<SdlKeyboardState>())
{
}

//======================================================================================================================
SdlKeyboard::~SdlKeyboard() = default;

//======================================================================================================================
void SdlKeyboard::update()
{
}

//======================================================================================================================
const input::KeyboardState& SdlKeyboard::getKeyboardState() const
{
    assert(_keyboardState);
    return *_keyboardState;
}

//======================================================================================================================
namespace {
    template <input_event::KeyboardEventKind kind>
    app_event::AppEvent makeKeyEvent(const SDL_KeyboardEvent& sdlKeyEv)
    {
        const auto ev = input_event::KeyboardEvent{input_event::KeyboardEventDetails<kind>{
            .keyCode = fromSdlKeyCode(sdlKeyEv.key),
            .keyScancode = fromSdlKeyScancode(sdlKeyEv.scancode),
            .keyMods = fromSdlKeyMods(sdlKeyEv.mod),
        }};

        LOG_CATEGORIZED(input::LogCategory::KeyboardEvents,
                        logger::LogMessageLevel::Brief,
                        "Received " << str(ev));

        return ev;
    }
}

//======================================================================================================================
Optional<app_event::AppEvent> SdlKeyboard::transformToAppEvent(const event_sys::NativeEvent& nativeEvent)
{
    assert(dynamic_cast<const sdl_event_sys::SdlNativeEvent*>(&nativeEvent));

    const auto& sdlNativeEvent = static_cast<const sdl_event_sys::SdlNativeEvent&>(nativeEvent);
    const auto& sdlEvent = sdlNativeEvent.getSdlEvent();

    switch (sdlEvent.type) {
    case SDL_EventType::SDL_EVENT_KEY_UP:
        return makeKeyEvent<input_event::KeyboardEventKind::KeyUp>(sdlEvent.key);
    case SDL_EventType::SDL_EVENT_KEY_DOWN:
        return sdlEvent.key.repeat ? makeKeyEvent<input_event::KeyboardEventKind::KeyRepeat>(sdlEvent.key)
                                   : makeKeyEvent<input_event::KeyboardEventKind::KeyDown>(sdlEvent.key);
    default: return std::nullopt;
    }
}
