#pragma once

#include <EventSys/EventMgr.h>

//======================================================================================================================
namespace sdl_event_sys {
    class SdlEventMgr final : public event_sys::EventMgr {
    private:
        Vector<uptr<event_sys::NativeEvent>> _fetchNativeEvents() override;
    };
}
