#include <Logger/BasicLogging.h>

#include <iostream>
#include <mutex>
#include <sstream>

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
    void _printToLog(std::ostream& outputStream, std::function<void(std::ostream&)> func)
    {
        std::ostringstream sstream;
        // TODO: add timestamp

        func(sstream);

        std::lock_guard lock{globalLogStreamContext.streamsMutex};
        outputStream << sstream.str() << std::endl;
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
