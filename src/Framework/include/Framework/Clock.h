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
        Nanoseconds getCurrentTicksSinceStart() const;

    private:
        friend class RenderableApplication;
        void _update();

    private:
        using ClockImpl = std::chrono::high_resolution_clock;
        using TimeMoment = ClockImpl::time_point;

        TimeMoment _startTime;
    };
}
