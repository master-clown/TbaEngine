#include <AppEvent/NativeEventListenersGuard.h>

using namespace app_event;

//======================================================================================================================
NativeEventListenersGuard::NativeEventListenersGuard(NativeEventListenersGuard&&) = default;

//======================================================================================================================
NativeEventListenersGuard::~NativeEventListenersGuard() = default;

//======================================================================================================================
NativeEventListenersGuard::NativeEventListenersGuard(NativeEventListeners& listeners,
                                                     const NativeEventListenerId listenerId)
    : _listeners(listeners)
    , _listenerId(listenerId)
{
}
