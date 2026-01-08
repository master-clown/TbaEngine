#pragma once

#include <AppEvent/AppEvent.h>
#include <AppEvent/NativeEventListenersGuard.h>

#include <Common/Stl/Optional.h>

//======================================================================================================================
namespace app_event {
    class NativeEvent;
    class NativeEventListeners;
}

//======================================================================================================================
namespace app_event {
    class NativeEventListener {
    public:
        explicit NativeEventListener(NativeEventListeners&);
        virtual ~NativeEventListener();

        virtual Optional<AppEvent> processNativeEvent(const NativeEvent&) = 0;

    private:
        NativeEventListenersGuard _guardInListeners;
    };
}
