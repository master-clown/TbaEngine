#include <AppEvent/NativeEventListener.h>

#include <AppEvent/NativeEventListeners.h>

using namespace app_event;

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
