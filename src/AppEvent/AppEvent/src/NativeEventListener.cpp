#include <AppEvent/NativeEventListener.h>

#include <AppEvent/NativeEventListeners.h>

using namespace app_event;

//======================================================================================================================
NativeEventListener::NativeEventListener(NativeEventListeners& listeners)
    : _guardInListeners(listeners.add(*this))
{
}

//======================================================================================================================
NativeEventListener::~NativeEventListener() = default;
