#pragma once

#include <AppEvent/NativeEventListenerId.h>

//======================================================================================================================
namespace app_event {
    class NativeEventListeners;
}

//======================================================================================================================
namespace app_event {
    class NativeEventListenersGuard final {
    public:
        NativeEventListenersGuard(NativeEventListenersGuard&&);
        ~NativeEventListenersGuard();

        //--------------------------------------------------------------------------------------------------------------
        NativeEventListenersGuard(const NativeEventListenersGuard&) = delete;
        NativeEventListenersGuard& operator=(const NativeEventListenersGuard&) = delete;

    private:
        friend class NativeEventListeners;
        NativeEventListenersGuard(NativeEventListeners&, NativeEventListenerId);

    private:
        NativeEventListeners& _listeners;
        NativeEventListenerId _listenerId;
    };
}
