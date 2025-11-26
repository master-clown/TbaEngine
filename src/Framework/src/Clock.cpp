#include <Framework/Clock.h>

//======================================================================================================================
using namespace framework;

//======================================================================================================================
Clock::Clock()
    : _startTime(ClockImpl::now())
{
}

//----------------------------------------------------------------------------------------------------------------------
Clock::~Clock() = default;

//======================================================================================================================
auto Clock::getRealTicksSinceStart() const -> Nanoseconds
{
    return std::chrono::duration_cast<Nanoseconds>(ClockImpl::now() - _startTime);
}

//======================================================================================================================
auto Clock::getCurrentRefreshTicks() const -> Nanoseconds
{
    return _currentRefreshTicks;
}

//======================================================================================================================
void Clock::_updateCurrentRefreshTicks()
{
    _currentRefreshTicks = getRealTicksSinceStart();
}
