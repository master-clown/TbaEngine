#pragma once

#include <string>

//======================================================================================================================
namespace input {
    //==================================================================================================================
    enum class LogCategory {
        KeyScancodeConversion,
        KeyboardState,
    };

    //------------------------------------------------------------------------------------------------------------------
    std::string str(LogCategory);

    //------------------------------------------------------------------------------------------------------------------
    LogCategory begin(LogCategory);
    LogCategory end(LogCategory);
    LogCategory operator++(LogCategory&);
    LogCategory operator*(LogCategory);
}
