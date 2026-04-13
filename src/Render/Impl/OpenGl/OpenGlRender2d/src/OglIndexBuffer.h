#pragma once

#include "TypedOglBuffer.h"

//======================================================================================================================
namespace opengl_render_2d {
    //==================================================================================================================
    // TODO: allow to work with batches of indexes
    //  (add `TypedOglBuffer::append(vector<BufferItem>)` for that)
    class OglIndexBuffer final {
    public:
        using VaoId = uint32;

        // TODO: use `const VertexArrayObject&` instead of `VaoId`
        explicit OglIndexBuffer(VaoId);

        using EboRawId = OglBuffer::BufferRawId;
        EboRawId getEboId() const;

        //--------------------------------------------------------------------------------------------------------------
        using Index = uint32;
        TypedOglBuffer<Index>& getUnderlyingBuffer();
        const TypedOglBuffer<Index>& getUnderlyingBuffer() const;

        //--------------------------------------------------------------------------------------------------------------
        using OglIndexType = uint32;
        static OglIndexType getOglIndexType();

    private:
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        TypedOglBuffer<Index> _buffer;
    };
}
