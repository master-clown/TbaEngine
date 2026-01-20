#pragma once

#include <Common/Integers.h>
#include <Common/String.h>

//======================================================================================================================
namespace mouse {
    //==================================================================================================================
    // - Origin: top-left window corner
    // - Ox: to the right
    // - Oy: down
    struct CursorPosition final {
        using WindowCoordinate = float;

        WindowCoordinate x = 0;
        WindowCoordinate y = 0;
    };

    //------------------------------------------------------------------------------------------------------------------
    String str(const CursorPosition&);
}
