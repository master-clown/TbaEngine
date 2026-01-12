#pragma once

#include <EventSys/EventQueue.h>
#include <EventSys/NativeEventListeners.h>

#include <AppEvent/AppEvent.h>
#include <Common/Memory.h>
#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace event_sys {
    class NativeEvent;
}

//======================================================================================================================
namespace event_sys {
    class EventMgr {
    public:
        virtual ~EventMgr();

        //--------------------------------------------------------------------------------------------------------------
        void pollEvents();

        //--------------------------------------------------------------------------------------------------------------
        app_event::AppEvent getNextEvent();

        //--------------------------------------------------------------------------------------------------------------
        EventQueue& getEventQueue() const;

        NativeEventListeners& getNativeEventListeners();
        const NativeEventListeners& getNativeEventListeners() const;

    private:
        virtual Vector<uptr<NativeEvent>> _fetchNativeEvents() = 0; // TODO: more efficient way to pass native events?

    private:
        mutable EventQueue _eventQueue; // change of the queue does not imply change of Mgr
        NativeEventListeners _nativeEventListeners;
    };
}
