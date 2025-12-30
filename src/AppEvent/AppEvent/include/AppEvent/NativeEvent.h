#pragma once

#include <Common/String.h>

//======================================================================================================================
namespace app_event {
    class NativeEvent {
    public:
        virtual ~NativeEvent();

        virtual String str() const = 0;
    };
}
