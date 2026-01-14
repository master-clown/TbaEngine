#include <Keyboard/KeyMods.h>

//======================================================================================================================
String keyboard::str(const keyboard::KeyMods mods)
{
    using En = keyboard::KeyMods;

    if (mods == En::None)
        return "KeyMods::None";

    String result = "KeyMods::";

    if ((mods & En::LCtrl) != En::None)
        result += "LCtrl+";
    if ((mods & En::RCtrl) != En::None)
        result += "RCtrl+";
    if ((mods & En::LAlt) != En::None)
        result += "LAlt+";
    if ((mods & En::RAlt) != En::None)
        result += "RAlt+";
    if ((mods & En::LShift) != En::None)
        result += "LShift+";
    if ((mods & En::RShift) != En::None)
        result += "RShift+";
    if ((mods & En::LGui) != En::None)
        result += "LGui+";
    if ((mods & En::RGui) != En::None)
        result += "RGui+";

    result.back() = '\0';

    return result;
}
