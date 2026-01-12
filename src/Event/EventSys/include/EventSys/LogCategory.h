#pragma once

#include <string>

//======================================================================================================================
namespace event_sys {
    //==================================================================================================================
    enum class LogCategory {
        EventConversionFromNative,
    };

    //------------------------------------------------------------------------------------------------------------------
    std::string str(LogCategory);

    //------------------------------------------------------------------------------------------------------------------
    LogCategory begin(LogCategory);
    LogCategory end(LogCategory);
    LogCategory operator++(LogCategory&);
    LogCategory operator*(LogCategory);
}
