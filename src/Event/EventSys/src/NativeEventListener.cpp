#include <EventSys/NativeEventListener.h>

#include <EventSys/NativeEventListeners.h>

using namespace event_sys;

//======================================================================================================================
NativeEventListener::NativeEventListener(NativeEventListeners& listeners)
    : _listeners(listeners)
    , _listenerId(_listeners._add(*this))
{
}

//======================================================================================================================
NativeEventListener::~NativeEventListener()
{
    _listeners._remove(_listenerId);
}
