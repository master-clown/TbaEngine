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
    class LoggingSettings final {
    public:
        //--------------------------------------------------------------------------------------------------------------
        static constexpr auto showTimeByDefault = std::nullopt;
        static void setShowTime(std::optional<bool> = showTimeByDefault);

        //--------------------------------------------------------------------------------------------------------------
        static constexpr auto coutAsDefaultLoggingStream = std::nullopt;
        static constexpr auto cerrAsDefaultErrorLoggingStream = std::nullopt;

        static void setLoggingStream(std::optional<std::ostream*> = coutAsDefaultLoggingStream);
        static void setErrorLoggingStream(std::optional<std::ostream*> = cerrAsDefaultErrorLoggingStream);
    };
}

//======================================================================================================================
// private macros
#define _TBA_LOG_IMPL(LOG_FUNC, msg)                                            \
    {                                                                           \
        logger::detail::LOG_FUNC([&](std::ostream& stream) { stream << msg; }); \
    }

//----------------------------------------------------------------------------------------------------------------------
#define _TBA_LOG_IMPL_FORMAT(LOG_FUNC, formatStr, ...)                                                          \
    {                                                                                                           \
        logger::detail::LOG_FUNC([&](std::ostream& stream) { stream << std::format(formatStr, __VA_ARGS__); }); \
    }

//----------------------------------------------------------------------------------------------------------------------
#define _TBA_CONCAT(A, B) A##B
#define _TBA_LOG_IMPL_WITH_FORMATTING_SELECTION(msg, ...) \
    _TBA_CONCAT(_TBA_LOG_IMPL, __VA_OPT__(_FORMAT))(logImpl, msg __VA_OPT__(, ) __VA_ARGS__)
#define _TBA_LOG_ERROR_WITH_FORMATTING_SELECTION(msg, ...) \
    _TBA_CONCAT(_TBA_LOG_IMPL, __VA_OPT__(_FORMAT))(logError, msg __VA_OPT__(, ) __VA_ARGS__)

//======================================================================================================================
#define LOG_ALWAYS(...) \
    _TBA_LOG_IMPL_WITH_FORMATTING_SELECTION(__VA_ARGS__);

//======================================================================================================================
#define LOG_ERROR(...) \
    _TBA_LOG_ERROR_WITH_FORMATTING_SELECTION(__VA_ARGS__);
