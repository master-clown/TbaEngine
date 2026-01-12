#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace input {
    class Keyboard;
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

    protected:
        void _setKeyboard(uptr<Keyboard>);

    private:
        event_sys::NativeEventListeners& _nativeEventListeners;
        uptr<Keyboard> _keyboard;
    };
}
