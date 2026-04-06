#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace opengl_api {
    class GpuOperationsCompletedEvent final {
    public:
        GpuOperationsCompletedEvent();
        ~GpuOperationsCompletedEvent();

        //--------------------------------------------------------------------------------------------------------------
        void reset(); // TODO: better name?
        void wait();

    private:
        struct _Pimpl;
        uptr<_Pimpl> _pimpl;
    };
}
