#pragma once

#include "OglVertexInfo.h"
#include "TypedOglBuffer.h"

//======================================================================================================================
namespace opengl_render_2d {
    class OglVertexBuffer final {
    public:
        using VaoId = uint32;

        // TODO: use `const VertexArrayObject&` instead of `VaoId`
        explicit OglVertexBuffer(const VaoId vaoId);

        using VboRawId = OglBuffer::BufferRawId;
        VboRawId getVboId() const;

        TypedOglBuffer<OglVertexInfo>& getUnderlyingBuffer();

    private:
        static void _staticAssertsOnTypedefs() noexcept;

    private:
        TypedOglBuffer<OglVertexInfo> _buffer;
    };
}
