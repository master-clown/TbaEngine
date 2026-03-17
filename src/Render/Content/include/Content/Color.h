#pragma once

#include <Common/Integers.h>

#include <limits>

//======================================================================================================================
namespace content {
    struct Color final {
        using ColorIntensity = uint8;

        ColorIntensity r = 0;
        ColorIntensity g = 0;
        ColorIntensity b = 0;
        ColorIntensity a = 0;

        //==============================================================================================================
        static const Color transparent;
        static const Color black;
        static const Color white;

        //==============================================================================================================
        static constexpr auto maxColorIntensity = std::numeric_limits<ColorIntensity>::max();
    };
}
