#pragma once

#include <Common/Integers.h>

#include <functional>

//======================================================================================================================
namespace opengl_render_2d {
    class OglBuffer {
    public:
        OglBuffer();
        virtual ~OglBuffer();

        size_t getCurrentAllocSizeInBytes() const;

        using BufferRawId = uint32;
        BufferRawId getBufferRawId() const;

        //--------------------------------------------------------------------------------------------------------------
        using MaxRequiredOffsetInBytes = size_t;

        struct NonPersistentBufferPtr final { // no guarantee the ptr is persistent
            void* ptr = nullptr;
        };

        void useBuffer(const MaxRequiredOffsetInBytes,
                       const std::function<void(const NonPersistentBufferPtr bufferPtr)>& action);

    private:
        using BufferSize = long;
        void _extendBuffer(const BufferSize newSize);

        //--------------------------------------------------------------------------------------------------------------
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        // TODO: transform to memory control parameter
        static constexpr BufferSize _baseChunkSizeInBytes = 1024 * 1024;

        BufferRawId _vboId = 0;
        BufferSize _currentAllocSizeInBytes = 1 * _baseChunkSizeInBytes;
        void* _bufferMappingPtr = nullptr;
    };
}
