#include <Logger/Logging.h>

#include <iostream>
#include <mutex>

//======================================================================================================================
struct LogStreamContext final {
    std::ostream* outStream = &std::cout;
    std::mutex outStreamMutex;
};

//----------------------------------------------------------------------------------------------------------------------
static LogStreamContext globalLogStreamContext;

//======================================================================================================================
void logger::detail::logImpl(std::function<void(std::ostream&)> func)
{
    std::lock_guard lock{globalLogStreamContext.outStreamMutex};

    // TODO: add timestamp

    auto& outStream = *globalLogStreamContext.outStream;

    func(outStream);
}

//======================================================================================================================
void logger::detail::logError(std::function<void(std::ostream&)> func)
{
    logImpl([func = std::move(func)](std::ostream& stream) {
        stream << "[ERROR] ";
        func(stream);
    });
}
