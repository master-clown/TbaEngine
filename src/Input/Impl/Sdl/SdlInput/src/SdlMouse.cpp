#include <SdlInput/SdlMouse.h>

#include "SdlCursorPosition.h"
#include "SdlMouseButton.h"
#include "SdlMouseState.h"

#include <AppEvent/AppEvent.h>
#include <EventInfo/EventInfo.hpp>
#include <Input/DeviceMgr.h>
#include <Input/Keyboard.h>
#include <Input/KeyboardState.h>
#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>
#include <SdlEventSys/SdlNativeEvent.h>

#include <cassert>

using namespace sdl_input;

//======================================================================================================================
SdlMouse::SdlMouse(event_sys::NativeEventListeners& nativeEventListeners,
                   const input::DeviceMgr& deviceMgr)
    : input::Mouse({.type = input::DeviceType::Mouse, .publicName = "SDL default mouse"})
    , event_sys::NativeEventListener(nativeEventListeners)
    , _deviceMgr(deviceMgr)
    , _mouseState(makeUPtr<SdlMouseState>())
{
}

//======================================================================================================================
SdlMouse::~SdlMouse() = default;

//======================================================================================================================
void SdlMouse::update()
{
}

//======================================================================================================================
void SdlMouse::setRelativeModeEnabled(SdlMouse::RelativeModeEnabled)
{
    // TODO
    throw std::runtime_error("Not implemented");
}

//======================================================================================================================
const input::MouseState& SdlMouse::getMouseState() const
{
    assert(_mouseState);
    return *_mouseState;
}

//======================================================================================================================
namespace {
    template <input_event::MouseEventKind kind>
    auto makeButtonEvent(const SDL_MouseButtonEvent& sdlBtnEv, const keyboard::KeyMods keyMods)
    {
        using namespace input_event;

        static_assert(kind == MouseEventKind::ButtonDown || kind == MouseEventKind::ButtonUp);

        return MouseEvent{MouseEventDetails<kind>{
            .button = fromSdlMouseButton(sdlBtnEv.button),
            .keyboardMods = keyMods,
        }};
    }
}

//======================================================================================================================
Optional<app_event::AppEvent> SdlMouse::transformToAppEvent(const event_sys::NativeEvent& nativeEvent)
{
    using namespace input_event;

    assert(dynamic_cast<const sdl_event_sys::SdlNativeEvent*>(&nativeEvent));

    const auto& sdlNativeEvent = static_cast<const sdl_event_sys::SdlNativeEvent&>(nativeEvent);
    const auto& sdlEvent = sdlNativeEvent.getSdlEvent();

    const auto& currentMods = _deviceMgr.getKeyboard().getKeyboardState().getModsState();

    const auto mouseEvent = [&] -> Optional<MouseEvent> {
        switch (sdlEvent.type) {
        case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
            return makeButtonEvent<MouseEventKind::ButtonDown>(sdlEvent.button, currentMods);
        case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
            return makeButtonEvent<MouseEventKind::ButtonUp>(sdlEvent.button, currentMods);
        case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
            return MouseEvent{MouseEventDetails<MouseEventKind::MouseMoved>{
                .cursorPos = fromSdlCursorPosition(sdlEvent.motion.x, sdlEvent.motion.y),
                .cursorPosDelta = fromSdlCursorPosition(sdlEvent.motion.xrel, sdlEvent.motion.yrel),
                .pressedButton = fromSdlMouseButtonFlags(sdlEvent.motion.state),
            }};
        case SDL_EventType::SDL_EVENT_MOUSE_WHEEL:
            return MouseEvent{MouseEventDetails<MouseEventKind::WheelMoved>{
                .x = sdlEvent.wheel.x,
                .y = sdlEvent.wheel.y,
            }};
        default: return std::nullopt;
        }
    }();

    if (!mouseEvent.has_value())
        return std::nullopt;

    LOG_CATEGORIZED(input::LogCategory::MouseEvents,
                    logger::LogMessageLevel::Brief,
                    "Received " << str(*mouseEvent));

    return *mouseEvent;
}
