#pragma once

#include <EventSys/NativeEventProvider.h>

//======================================================================================================================
namespace sdl_event_sys {
    class SdlEventProvider final : public event_sys::NativeEventProvider {
    private:
        Vector<uptr<event_sys::NativeEvent>> fetchNewNativeEvents() override;
    };
}
