#include <Input/Keyboard.h>

using namespace input;

//======================================================================================================================
Keyboard::Keyboard(DeviceInfo deviceInfo)
    : Device(std::move(deviceInfo))
{
}
