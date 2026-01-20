#include <Input/LogCategory.h>

#include <type_traits>
#include <utility>

using namespace input;

//======================================================================================================================
std::string input::str(const LogCategory cat)
{
    using Enum = LogCategory;

    switch (cat) {
    case Enum::KeyScancodeConversion: return "input::LogCategory::KeyScancodeConversion";
    case Enum::KeyCodeConversion: return "input::LogCategory::KeyCodeConversion";
    case Enum::KeyboardEvents: return "input::LogCategory::KeyboardEvents";
    case Enum::KeyboardState: return "input::LogCategory::KeyboardState";
    case Enum::MouseButtonConversion: return "input::LogCategory::MouseButtonConversion";
    case Enum::MouseEvents: return "input::LogCategory::MouseEvents";
    default: std::unreachable();
    }
}

//======================================================================================================================
LogCategory input::begin(LogCategory)
{
    return LogCategory::KeyScancodeConversion;
}

//======================================================================================================================
LogCategory input::end(LogCategory)
{
    auto theEnd = LogCategory::MouseEvents;
    return ++theEnd;
}

//======================================================================================================================
LogCategory input::operator++(LogCategory& arg)
{
    return arg = static_cast<LogCategory>(static_cast<std::underlying_type_t<LogCategory>>(arg) + 1);
}

//======================================================================================================================
LogCategory input::operator*(const LogCategory arg)
{
    return arg;
}
