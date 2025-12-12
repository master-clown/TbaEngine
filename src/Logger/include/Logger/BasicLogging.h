#pragma once

#include <format>
#include <functional>
#include <optional>
#include <ostream>

//======================================================================================================================
namespace logger::detail {
    //==================================================================================================================
    void logImpl(std::function<void(std::ostream&)>);
    void logError(std::function<void(std::ostream&)>);
}

//======================================================================================================================
namespace logger {
    //==================================================================================================================
    constexpr auto coutAsDefaultLoggingStream = std::nullopt;
    constexpr auto cerrAsDefaultErrorLoggingStream = std::nullopt;

    //==================================================================================================================
    void setLoggingStream(std::optional<std::ostream*> = coutAsDefaultLoggingStream);
    void setErrorLoggingStream(std::optional<std::ostream*> = cerrAsDefaultErrorLoggingStream);
}

//======================================================================================================================
// private macros
#define _LOG_IMPL(LOG_FUNC, msg)                                                \
    {                                                                           \
        logger::detail::LOG_FUNC([&](std::ostream& stream) { stream << msg; }); \
    }

//----------------------------------------------------------------------------------------------------------------------
#define _LOG_IMPL_FORMAT(LOG_FUNC, formatStr, ...)                                                              \
    {                                                                                                           \
        logger::detail::LOG_FUNC([&](std::ostream& stream) { stream << std::format(formatStr, __VA_ARGS__); }); \
    }

//----------------------------------------------------------------------------------------------------------------------
#define _CONCAT(A, B) A##B
#define _LOG_IMPL_WITH_FORMATTING_SELECTION(msg, ...) \
    _CONCAT(_LOG_IMPL, __VA_OPT__(_FORMAT))(logImpl, msg __VA_OPT__(, ) __VA_ARGS__)
#define _LOG_ERROR_WITH_FORMATTING_SELECTION(msg, ...) \
    _CONCAT(_LOG_IMPL, __VA_OPT__(_FORMAT))(logError, msg __VA_OPT__(, ) __VA_ARGS__)

//======================================================================================================================
#define LOG_ALWAYS(...) \
    _LOG_IMPL_WITH_FORMATTING_SELECTION(__VA_ARGS__);

//======================================================================================================================
#define LOG_ERROR(...) \
    _LOG_ERROR_WITH_FORMATTING_SELECTION(__VA_ARGS__);
