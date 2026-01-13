#pragma once

#include <Winsys/Window.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners;
}

//======================================================================================================================
namespace winsys {
    class WindowMgr {
    public:
        explicit WindowMgr(event_sys::NativeEventListeners&);
        virtual ~WindowMgr();

        //--------------------------------------------------------------------------------------------------------------
        virtual uptr<Window> createWindow(WindowOptions) = 0;

        //--------------------------------------------------------------------------------------------------------------
        event_sys::NativeEventListeners& getNativeEventListeners();

    private:
        event_sys::NativeEventListeners& _nativeEventListeners;
    };
}
