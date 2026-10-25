#pragma once

#include <Common/Integers.h>

#include <chrono>

//======================================================================================================================
namespace framework {
    class Clock final {
    public:
        Clock();
        ~Clock();

        using Nanoseconds = std::chrono::duration<uint64, std::nano>;
        using Seconds = std::chrono::duration<double, std::ratio<1, 1>>;
        Nanoseconds getRealTicksSinceStart() const;
        Nanoseconds getCurrentRefreshTicks() const noexcept;
        Nanoseconds getDeltaSinceLastUpdate() const noexcept;
        Seconds getDeltaSinceLastUpdateInSeconds() const noexcept;

    private:
        friend class RenderableApplication;
        void _updateCurrentRefreshTicks();

    private:
        using ClockImpl = std::chrono::high_resolution_clock;
        using TimeMoment = ClockImpl::time_point;

        TimeMoment _startTime;
        Nanoseconds _currentRefreshTicks{};
        Nanoseconds _prevRefreshTicks{};
        Nanoseconds _lastDelta{};
        Seconds _lastDeltaInSeconds{};
    };
}
