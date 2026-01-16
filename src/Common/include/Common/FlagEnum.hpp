#pragma once

#include <Common/FlagEnum.h>

#include <type_traits>

//======================================================================================================================
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum operator&(const FlagEnum& arg1, const FlagEnum& arg2)
{
    return static_cast<FlagEnum>(
        static_cast<std::underlying_type_t<FlagEnum>>(arg1) &
        static_cast<std::underlying_type_t<FlagEnum>>(arg2));
}

//----------------------------------------------------------------------------------------------------------------------
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum& operator&=(FlagEnum& self, const FlagEnum& arg)
{
    return self = self & arg;
}

//======================================================================================================================
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum operator|(const FlagEnum& arg1, const FlagEnum& arg2)
{
    return static_cast<FlagEnum>(
        static_cast<std::underlying_type_t<FlagEnum>>(arg1) |
        static_cast<std::underlying_type_t<FlagEnum>>(arg2));
}

//----------------------------------------------------------------------------------------------------------------------
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum& operator|=(FlagEnum& self, const FlagEnum& arg)
{
    return self = self | arg;
}
