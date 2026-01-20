#pragma once

#include <Input/Device.h>

//======================================================================================================================
namespace input {
    class MouseState;
}

//======================================================================================================================
namespace input {
    class Mouse : public Device {
    public:
        explicit Mouse(DeviceInfo);

        using RelativeModeEnabled = bool;
        virtual void setRelativeModeEnabled(RelativeModeEnabled) = 0;

        virtual const MouseState& getMouseState() const = 0;
    };
}
