#pragma once

#include <EventSys/EventQueue.h>
#include <EventSys/NativeEventListeners.h>

#include <AppEvent/AppEvent.h>
#include <Common/Memory.h>

//======================================================================================================================
namespace event_sys {
    class NativeEvent;
    class NativeEventProvider;
}

//======================================================================================================================
namespace event_sys {
    class EventMgr final {
    public:
        explicit EventMgr(uptr<NativeEventProvider>);

        //--------------------------------------------------------------------------------------------------------------
        void pollEvents();

        //--------------------------------------------------------------------------------------------------------------
        app_event::AppEvent getNextEvent();

        //--------------------------------------------------------------------------------------------------------------
        EventQueue& getEventQueue() const;

        NativeEventListeners& getNativeEventListeners();
        const NativeEventListeners& getNativeEventListeners() const;

    private:
        uptr<NativeEventProvider> _nativeEventProvider;
        mutable EventQueue _eventQueue; // change of the queue does not imply change of Mgr
        NativeEventListeners _nativeEventListeners;
    };
}
