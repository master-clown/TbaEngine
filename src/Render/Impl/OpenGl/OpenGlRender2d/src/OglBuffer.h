#pragma once

#include "VboRaii.h"

#include <Common/Integers.h>

#include <functional>

//======================================================================================================================
namespace opengl_render_2d {
    class OglBuffer {
    public:
        using BufferExtendedCallback = std::function<void()>;
        explicit OglBuffer(BufferExtendedCallback = [] { });

        virtual ~OglBuffer();

        using BufferSizeInBytes = VboRaii::BufferSizeInBytes;
        BufferSizeInBytes getCurrentAllocSizeInBytes() const;

        using BufferRawId = VboRaii::BufferRawId;
        BufferRawId getBufferRawId() const;

        //--------------------------------------------------------------------------------------------------------------
        using MaxRequiredOffsetInBytes = size_t;

        struct NonPersistentBufferPtr final { // can change due to buffer extensions
            void* ptr = nullptr;
        };

        void useBuffer(const MaxRequiredOffsetInBytes,
                       const std::function<void(const NonPersistentBufferPtr bufferPtr)>& action);

    private:
        void _extendBuffer(BufferSizeInBytes newSize);

    private:
        // TODO: transform to memory control parameter
        static constexpr BufferSizeInBytes _baseChunkSizeInBytes = 1024 * 1024;

        BufferExtendedCallback _bufferExtendedCallback;
        VboRaii _currentBuffer;
    };
}
