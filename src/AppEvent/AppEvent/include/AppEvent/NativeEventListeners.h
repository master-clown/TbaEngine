#pragma once

#include <AppEvent/NativeEventListenerId.h>

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
