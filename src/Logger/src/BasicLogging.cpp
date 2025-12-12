#include <Logger/BasicLogging.h>

#include <atomic>
#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <sstream>

//======================================================================================================================
namespace {
    struct LogSettingsData final {
        std::ostream* outStream = &std::cout;
        std::ostream* errorStream = &std::cerr;
        std::mutex streamsMutex;
        std::atomic<bool> showTime = true;
    };
}

//----------------------------------------------------------------------------------------------------------------------
static LogSettingsData globalLogSettingsData;

//======================================================================================================================
namespace {
    void _printToLog(std::ostream& outputStream, std::function<void(std::ostream&)> func)
    {
        std::ostringstream sstream;

        if (globalLogSettingsData.showTime.load()) {
            const auto msgTimePoint = std::chrono::system_clock::now();

            // TODO: %S gives the fractional part too. Ensure its format is standartized.
            sstream << std::format("{:%y%m%dT%H%M%S}> ", msgTimePoint);
        }

        func(sstream);

        std::lock_guard lock{globalLogSettingsData.streamsMutex};
        outputStream << sstream.str() << std::endl;
    }
}

//======================================================================================================================
void logger::detail::logImpl(std::function<void(std::ostream&)> func)
{
    _printToLog(*globalLogSettingsData.outStream, std::move(func));
}

//======================================================================================================================
void logger::detail::logError(std::function<void(std::ostream&)> func)
{
    _printToLog(*globalLogSettingsData.errorStream, [func = std::move(func)](std::ostream& stream) {
        stream << "[ERROR] ";
        func(stream);
    });
}

//======================================================================================================================
void logger::LoggingSettings::setShowTime(std::optional<bool> showTimeOpt)
{
    if (!showTimeOpt.has_value())
        showTimeOpt = true;

    globalLogSettingsData.showTime.store(*showTimeOpt);
}

//======================================================================================================================
void logger::LoggingSettings::setLoggingStream(std::optional<std::ostream*> streamOpt)
{
    if (!streamOpt.has_value() || streamOpt == coutAsDefaultLoggingStream)
        streamOpt = &std::cout;

    std::lock_guard lock{globalLogSettingsData.streamsMutex};

    globalLogSettingsData.outStream = *streamOpt;
}

//======================================================================================================================
void logger::LoggingSettings::setErrorLoggingStream(std::optional<std::ostream*> streamOpt)
{
    if (!streamOpt.has_value() || streamOpt == cerrAsDefaultErrorLoggingStream)
        streamOpt = &std::cerr;

    std::lock_guard lock{globalLogSettingsData.streamsMutex};

    globalLogSettingsData.errorStream = *streamOpt;
}
