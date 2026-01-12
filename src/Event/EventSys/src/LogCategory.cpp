#include <EventSys/LogCategory.h>

#include <type_traits>
#include <utility>

using namespace event_sys;

//======================================================================================================================
std::string event_sys::str(const LogCategory cat)
{
    using Enum = LogCategory;

    switch (cat) {
    case Enum::EventConversionFromNative: return "event_sys::LogCategory::EventConversionFromNative";
    default: std::unreachable();
    }
}

//======================================================================================================================
LogCategory event_sys::begin(LogCategory)
{
    return LogCategory::EventConversionFromNative;
}

//======================================================================================================================
LogCategory event_sys::end(LogCategory)
{
    auto theEnd = LogCategory::EventConversionFromNative;
    return ++theEnd;
}

//======================================================================================================================
LogCategory event_sys::operator++(LogCategory& arg)
{
    return arg = static_cast<LogCategory>(static_cast<std::underlying_type_t<LogCategory>>(arg) + 1);
}

//======================================================================================================================
LogCategory event_sys::operator*(const LogCategory arg)
{
    return arg;
}
