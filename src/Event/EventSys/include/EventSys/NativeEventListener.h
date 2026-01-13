#pragma once

#include <EventSys/NativeEventListenerId.h>

#include <Common/Stl/Optional.h>

//======================================================================================================================
namespace app_event {
    class AppEvent;
}

//======================================================================================================================
namespace event_sys {
    class NativeEvent;
    class NativeEventListeners;
}

//======================================================================================================================
namespace event_sys {
    class NativeEventListener {
    public:
        explicit NativeEventListener(NativeEventListeners&);
        virtual ~NativeEventListener();

        virtual Optional<app_event::AppEvent> transformToAppEvent(const NativeEvent&) = 0;

    private:
        NativeEventListeners& _listeners;
        NativeEventListenerId _listenerId;
    };
}
