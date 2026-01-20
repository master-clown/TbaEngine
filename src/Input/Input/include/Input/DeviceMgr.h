#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace input {
    class Keyboard;
    class Mouse;
}

//======================================================================================================================
namespace input {
    //==================================================================================================================
    class DeviceMgr {
    public:
        explicit DeviceMgr(event_sys::NativeEventListeners&);
        virtual ~DeviceMgr();

        //--------------------------------------------------------------------------------------------------------------
        void update();

        //--------------------------------------------------------------------------------------------------------------
        event_sys::NativeEventListeners& getNativeEventListeners();

        //--------------------------------------------------------------------------------------------------------------
        Keyboard& getKeyboard();
        const Keyboard& getKeyboard() const;

        Mouse& getMouse();
        const Mouse& getMouse() const;

    protected:
        void _setKeyboard(uptr<Keyboard>);
        void _setMouse(uptr<Mouse>);

    private:
        event_sys::NativeEventListeners& _nativeEventListeners;
        uptr<Keyboard> _keyboard;
        uptr<Mouse> _mouse;
    };
}
