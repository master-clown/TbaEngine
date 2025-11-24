#pragma once

#include <format>
#include <string>

//======================================================================================================================
using String = std::string;

//======================================================================================================================
template <class... Args>
String str(Args&&... args)
{
    return std::to_string(std::forward<Args>(args)...);
}

//======================================================================================================================
template <class... Args>
String strFormat(std::basic_format_string<typename String::value_type,
                                          std::type_identity_t<Args>...> formatStr,
                 Args&&... args)
{
    return std::format(std::move(formatStr), std::forward<Args>(args)...);
}
