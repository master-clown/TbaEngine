#pragma once

#include <Input/DeviceType.h>

#include <string>

//======================================================================================================================
namespace input {
    struct DeviceInfo final {
        DeviceType type;
        std::string publicName;
    };
}
