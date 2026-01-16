#pragma once

#include <Input/DeviceInfo.h>

//======================================================================================================================
namespace input {
    class Device {
    public:
        explicit Device(DeviceInfo);
        virtual ~Device();

        //--------------------------------------------------------------------------------------------------------------
        virtual void update() = 0;

        //--------------------------------------------------------------------------------------------------------------
        const DeviceInfo& getDeviceInfo() const;

    private:
        DeviceInfo _deviceInfo;
    };
}
