#pragma once

#include <Common/Integers.h>

//======================================================================================================================
namespace framework {
    struct RefreshRateOptions final {
        using TimesPerSecond = uint16;

        TimesPerSecond maxLogicRefreshRatePerSecond = 60;
        uint16 logicRefreshesPerRenderFrame = 1;

        static constexpr TimesPerSecond unlimitedRefreshRate{0};
    };
}
