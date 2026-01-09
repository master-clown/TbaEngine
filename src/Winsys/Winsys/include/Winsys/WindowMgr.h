#pragma once

#include <Winsys/Window.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace app_event {
    class NativeEventListeners;
}

//======================================================================================================================
namespace winsys {
    class WindowMgr {
    public:
        explicit WindowMgr(app_event::NativeEventListeners&);
        virtual ~WindowMgr();

        //--------------------------------------------------------------------------------------------------------------
        virtual uptr<Window> createWindow(WindowOptions) = 0;

        //--------------------------------------------------------------------------------------------------------------
        app_event::NativeEventListeners& getNativeEventListeners();

    private:
        app_event::NativeEventListeners& _nativeEventListeners;
    };
}
