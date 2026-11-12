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
auto Clock::getCurrentRefreshTicks() const noexcept -> Nanoseconds
{
    return _currentRefreshTicks;
}

//======================================================================================================================
auto Clock::getDeltaSinceLastUpdate() const noexcept -> Nanoseconds
{
    return _lastDelta;
}

//======================================================================================================================
auto Clock::getDeltaSinceLastUpdateInSeconds() const noexcept -> Seconds
{
    return _lastDeltaInSeconds;
}

//======================================================================================================================
void Clock::_updateCurrentRefreshTicks()
{
    _prevRefreshTicks = _currentRefreshTicks;
    _currentRefreshTicks = getRealTicksSinceStart();
    _lastDelta = _currentRefreshTicks - _prevRefreshTicks;
    _lastDeltaInSeconds = std::chrono::duration_cast<Seconds>(_lastDelta);
}
