#include <AppEvent/LogCategory.h>

#include <type_traits>
#include <utility>

using namespace app_event;

//======================================================================================================================
std::string app_event::str(const LogCategory cat)
{
    using Enum = LogCategory;

    switch (cat) {
    case Enum::EventConversionFromNative: return "app_event::LogCategory::EventConversionFromNative";
    default: std::unreachable();
    }
}

//======================================================================================================================
LogCategory app_event::begin(LogCategory)
{
    return LogCategory::EventConversionFromNative;
}

//======================================================================================================================
LogCategory app_event::end(LogCategory)
{
    auto theEnd = LogCategory::EventConversionFromNative;
    return ++theEnd;
}

//======================================================================================================================
LogCategory app_event::operator++(LogCategory& arg)
{
    return arg = static_cast<LogCategory>(static_cast<std::underlying_type_t<LogCategory>>(arg) + 1);
}

//======================================================================================================================
LogCategory app_event::operator*(const LogCategory arg)
{
    return arg;
}
