#pragma once

#include <Common/Integers.h>

//======================================================================================================================
namespace content {
    struct Color final {
        uint8 r = 0;
        uint8 g = 0;
        uint8 b = 0;
        uint8 a = 0;

        static const Color transparent;
        static const Color black;
        static const Color white;
    };
}
