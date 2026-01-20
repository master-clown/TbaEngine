#pragma once

#include <string>

//======================================================================================================================
namespace input {
    //==================================================================================================================
    enum class LogCategory {
        KeyScancodeConversion,
        KeyCodeConversion,
        KeyboardEvents,
        KeyboardState,
        MouseButtonConversion,
        MouseEvents,
    };

    //------------------------------------------------------------------------------------------------------------------
    std::string str(LogCategory);

    //------------------------------------------------------------------------------------------------------------------
    LogCategory begin(LogCategory);
    LogCategory end(LogCategory);
    LogCategory operator++(LogCategory&);
    LogCategory operator*(LogCategory);
}
