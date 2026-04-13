#include <OpenGlApi/GpuOperationsCompletedEvent.h>

#include <OpenGlApi/OpenGlApi.h>

#include <Common/Integers.h>

#include <cassert>

//======================================================================================================================
using opengl_api::GpuOperationsCompletedEvent;

//======================================================================================================================
struct GpuOperationsCompletedEvent::_Pimpl final {
    GLsync syncObject = 0;
};

//======================================================================================================================
GpuOperationsCompletedEvent::GpuOperationsCompletedEvent()
    : _pimpl(makeUPtr<_Pimpl>())
{
}

//======================================================================================================================
GpuOperationsCompletedEvent::~GpuOperationsCompletedEvent() = default;

//======================================================================================================================
void GpuOperationsCompletedEvent::reset()
{
    if (_pimpl->syncObject)
        glDeleteSync(_pimpl->syncObject);

    using Flags = GLbitfield;

    _pimpl->syncObject = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, Flags{0});
    assert(_pimpl->syncObject);
}

//======================================================================================================================
void GpuOperationsCompletedEvent::wait()
{
    if (!_pimpl->syncObject)
        return;

    while (true) {
        static constexpr uint64 waitTimeoutInNsec = 500 * 1000;

        const auto waitResult = glClientWaitSync(_pimpl->syncObject, GL_SYNC_FLUSH_COMMANDS_BIT, waitTimeoutInNsec);
        assert(waitResult != GL_WAIT_FAILED);

        if (waitResult == GL_ALREADY_SIGNALED || waitResult == GL_CONDITION_SATISFIED)
            return;
    }
}
