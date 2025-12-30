#pragma once

#include <string>

//======================================================================================================================
namespace app_event {
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
