#pragma once

#include <Common/Memory.h>
#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace event_sys {
    class NativeEvent;
}

//======================================================================================================================
namespace event_sys {
    class NativeEventProvider {
    public:
        virtual ~NativeEventProvider();

        // TODO: better container?
        virtual Vector<uptr<NativeEvent>> fetchNewNativeEvents() = 0;
    };
}
