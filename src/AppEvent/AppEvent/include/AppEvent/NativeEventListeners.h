#pragma once

#include <AppEvent/NativeEventListenersGuard.h>

#include <Common/Stl/HashMap.h>

#include <functional>
#include <utility>

//======================================================================================================================
namespace app_event {
    class NativeEventListener;
}

//======================================================================================================================
namespace app_event {
    class NativeEventListeners final {
    public:
        NativeEventListeners();
        ~NativeEventListeners();

        //--------------------------------------------------------------------------------------------------------------
        NativeEventListenersGuard add(NativeEventListener&);

        //--------------------------------------------------------------------------------------------------------------
        enum class ListenerTraversalAction {
            Continue,
            Break,
        };

        void forEach(std::function<ListenerTraversalAction(NativeEventListener&)>);

    private:
        friend class NativeEventListenersGuard;
        void _remove(NativeEventListenerId);

        //--------------------------------------------------------------------------------------------------------------
        static NativeEventListenerId _getNextListenerId();

    private:
        using NativeEventListenerRef = std::reference_wrapper<NativeEventListener>;
        HashMap<NativeEventListenerId, NativeEventListenerRef> _listenersMap;
    };
}
