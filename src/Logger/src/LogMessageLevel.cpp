#include <Logger/LogMessageLevel.h>

#include <type_traits>
#include <utility>

//======================================================================================================================
std::string logger::str(const logger::LogMessageLevel msg)
{
    using Enum = logger::LogMessageLevel;

    switch (msg) {
    case Enum::Silent: return "LogMessageLevel::Silent";
    case Enum::Brief: return "LogMessageLevel::Brief";
    case Enum::Normal: return "LogMessageLevel::Normal";
    case Enum::Verbose: return "LogMessageLevel::Verbose";
    case Enum::Trace: return "LogMessageLevel::Trace";
    default: std::unreachable();
    }
}

//======================================================================================================================
bool logger::operator<=(const LogMessageLevel lhs, const LogMessageLevel rhs)
{
    return static_cast<std::underlying_type_t<LogMessageLevel>>(lhs) <=
        static_cast<std::underlying_type_t<LogMessageLevel>>(rhs);
}
