#include <Logger/LogMessageLevel.h>

#include <type_traits>
#include <utility>

//======================================================================================================================
std::string logger::str(const logger::LogMessageLevel msg)
{
    using Enum = logger::LogMessageLevel;

    switch (msg) {
    case Enum::Silent: return "Silent";
    case Enum::Brief: return "Brief";
    case Enum::Normal: return "Normal";
    case Enum::Verbose: return "Verbose";
    case Enum::Trace: return "Trace";
    default: std::unreachable();
    }
}

//======================================================================================================================
bool logger::operator<=(const LogMessageLevel lhs, const LogMessageLevel rhs)
{
    return static_cast<std::underlying_type_t<LogMessageLevel>>(lhs) <=
        static_cast<std::underlying_type_t<LogMessageLevel>>(rhs);
}
