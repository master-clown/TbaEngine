#pragma once

#include <Common/Memory.h>
#include <EventSys/NativeEventListener.h>
#include <Input/Keyboard.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace sdl_input {
    class SdlKeyboard final : public input::Keyboard,
                              public event_sys::NativeEventListener {
    public:
        explicit SdlKeyboard(event_sys::NativeEventListeners&);
        ~SdlKeyboard();

        //--------------------------------------------------------------------------------------------------------------
        void update() override;

        const input::KeyboardState& getKeyboardState() const override;

        //--------------------------------------------------------------------------------------------------------------
        Optional<app_event::AppEvent> transformToAppEvent(const event_sys::NativeEvent&) override;

    private:
        uptr<input::KeyboardState> _keyboardState;
    };
}
