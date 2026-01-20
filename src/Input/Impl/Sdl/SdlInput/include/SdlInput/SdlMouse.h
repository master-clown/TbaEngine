#pragma once

#include <Common/Memory.h>
#include <EventSys/NativeEventListener.h>
#include <Input/Mouse.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace input {
    class DeviceMgr;
}

//======================================================================================================================
namespace sdl_input {
    class SdlMouse final : public input::Mouse,
                           public event_sys::NativeEventListener {
    public:
        explicit SdlMouse(event_sys::NativeEventListeners&, const input::DeviceMgr&);
        ~SdlMouse();

        //--------------------------------------------------------------------------------------------------------------
        void update() override;

        //--------------------------------------------------------------------------------------------------------------
        void setRelativeModeEnabled(RelativeModeEnabled) override;
        const input::MouseState& getMouseState() const override;

        //--------------------------------------------------------------------------------------------------------------
        Optional<app_event::AppEvent> transformToAppEvent(const event_sys::NativeEvent&) override;

    private:
        uptr<input::MouseState> _mouseState;
        const input::DeviceMgr& _deviceMgr;
        RelativeModeEnabled _relativeModEnabled = false;
    };
}
