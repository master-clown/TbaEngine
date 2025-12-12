#include <Logger/BasicLogging.h>

#include <iostream>
#include <mutex>

//======================================================================================================================
struct LogStreamContext final {
    std::ostream* outStream = &std::cout;
    std::ostream* errorStream = &std::cerr;
    std::mutex streamsMutex;
};

//----------------------------------------------------------------------------------------------------------------------
static LogStreamContext globalLogStreamContext;

//======================================================================================================================
namespace {
    void _printToLog(std::ostream& stream, std::function<void(std::ostream&)> func)
    {
        std::lock_guard lock{globalLogStreamContext.streamsMutex};

        // TODO: add timestamp

        func(stream);
    }
}

//======================================================================================================================
void logger::detail::logImpl(std::function<void(std::ostream&)> func)
{
    _printToLog(*globalLogStreamContext.outStream, std::move(func));
}

//======================================================================================================================
void logger::detail::logError(std::function<void(std::ostream&)> func)
{
    _printToLog(*globalLogStreamContext.errorStream, [func = std::move(func)](std::ostream& stream) {
        stream << "[ERROR] ";
        func(stream);
    });
}

//======================================================================================================================
void logger::setLoggingStream(std::optional<std::ostream*> streamOpt)
{
    if (!streamOpt.has_value() || streamOpt == coutAsDefaultLoggingStream)
        streamOpt = &std::cout;

    std::lock_guard lock{globalLogStreamContext.streamsMutex};

    globalLogStreamContext.outStream = *streamOpt;
}

//======================================================================================================================
void logger::setErrorLoggingStream(std::optional<std::ostream*> streamOpt)
{
    if (!streamOpt.has_value() || streamOpt == cerrAsDefaultErrorLoggingStream)
        streamOpt = &std::cerr;

    std::lock_guard lock{globalLogStreamContext.streamsMutex};

    globalLogStreamContext.errorStream = *streamOpt;
}
