#pragma once

#include <AppEvent/AppEvent.h>
#include <AppEvent/EventQueue.h>
#include <AppEvent/NativeEventListeners.h>

#include <Common/Memory.h>
#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace app_event {
    class NativeEvent;
}

//======================================================================================================================
namespace app_event {
    class AppEventMgr {
    public:
        virtual ~AppEventMgr();

        //--------------------------------------------------------------------------------------------------------------
        void pollEvents();

        //--------------------------------------------------------------------------------------------------------------
        AppEvent getNextEvent();

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
