#pragma once

#include <Input/DeviceMgr.h>

//======================================================================================================================
namespace sdl_input {
    //==================================================================================================================
    class SdlDeviceMgr final : public input::DeviceMgr {
    public:
        explicit SdlDeviceMgr(event_sys::NativeEventListeners&);
    };
}
