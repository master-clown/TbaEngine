#include <Logger/LogMessageLevel.h>

#include <type_traits>

//======================================================================================================================
bool logger::operator<=(const LogMessageLevel lhs, const LogMessageLevel rhs)
{
    return static_cast<std::underlying_type_t<LogMessageLevel>>(lhs) <=
        static_cast<std::underlying_type_t<LogMessageLevel>>(rhs);
}
