#pragma once

#include <EventSys/NativeEventListenerId.h>

#include <Common/Stl/HashMap.h>

#include <functional>
#include <utility>

//======================================================================================================================
namespace event_sys {
    class NativeEventListener;
}

//======================================================================================================================
namespace event_sys {
    class NativeEventListeners final {
    public:
        NativeEventListeners();
        ~NativeEventListeners();

        //--------------------------------------------------------------------------------------------------------------
        enum class ListenerTraversalAction {
            Continue,
            Break,
        };

        void forEach(std::function<ListenerTraversalAction(NativeEventListener&)>);

    private:
        friend class NativeEventListener;
        NativeEventListenerId _add(NativeEventListener&);
        void _remove(NativeEventListenerId);

        //--------------------------------------------------------------------------------------------------------------
        static NativeEventListenerId _getNextListenerId();

    private:
        using NativeEventListenerRef = std::reference_wrapper<NativeEventListener>;
        HashMap<NativeEventListenerId, NativeEventListenerRef> _listenersMap;
    };
}
