#pragma once

#include <type_traits>

//======================================================================================================================
template <class ToNum, class FromNum>
ToNum numericCast(const FromNum fromNum)
{
    static_assert(std::is_arithmetic_v<FromNum>);
    static_assert(std::is_arithmetic_v<ToNum>);

    // TODO: implement assert for range check

    return static_cast<ToNum>(fromNum);
}
