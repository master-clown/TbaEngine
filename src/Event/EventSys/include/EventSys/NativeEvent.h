#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace event_sys {
    class NativeEvent {
    public:
        virtual ~NativeEvent();

        virtual String str() const = 0;
    };
}
