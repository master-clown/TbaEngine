#pragma once

#include <Common/FlagEnum.hpp>
#include <Common/Integers.h>

//======================================================================================================================
namespace input {
    enum class KeyMods : uint16;
}

//======================================================================================================================
template <>
inline constexpr bool isFlagEnum<input::KeyMods> = true;

//======================================================================================================================
namespace input {
    enum class KeyMods : uint16 {
        None = 0,
        LShift = 1 << 0,
        RShift = 1 << 1,
        LCtrl = 1 << 2,
        RCtrl = 1 << 3,
        LAlt = 1 << 4,
        RAlt = 1 << 5,
        LGui = 1 << 6,
        RGui = 1 << 7,
        //--------------------------------------------------------------------------------------------------------------
        Shift = LShift | RShift,
        Ctrl = LCtrl | RCtrl,
        Alt = LAlt | RAlt,
        Gui = LGui | RGui,
    };
}
