#include <Logger/BasicLogging.h>

#include <iostream>
#include <mutex>
#include <sstream>

//======================================================================================================================
namespace {
    struct LogSettingsData final {
        std::ostream* outStream = &std::cout;
        std::ostream* errorStream = &std::cerr;
        std::mutex streamsMutex;
    };
}

//----------------------------------------------------------------------------------------------------------------------
static LogSettingsData globalLogSettingsData;

//======================================================================================================================
namespace {
    void _printToLog(std::ostream& outputStream, std::function<void(std::ostream&)> func)
    {
        std::ostringstream sstream;
        // TODO: add timestamp

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
