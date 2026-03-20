#include "OglVertexBuffer.h"

// TODO: single cpp for avoiding many inclusions of this header?
#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
using opengl_render_2d::OglVertexBuffer;
using opengl_render_2d::OglVertexInfo;
using opengl_render_2d::TypedOglBuffer;

//======================================================================================================================
void OglVertexBuffer::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<VboRawId, GLuint>);
    static_assert(std::is_same_v<VaoId, GLuint>);
}

//======================================================================================================================
OglVertexBuffer::OglVertexBuffer(const VaoId vaoId)
{
    // TODO: assert(vao.isBinded());

    static constexpr GLuint vboBindingPoint = 0;

    glVertexArrayVertexBuffer(vaoId, vboBindingPoint, _buffer.getBufferRawId(), 0, sizeof(OglVertexInfo));

    glEnableVertexArrayAttrib(vaoId, 0);
    glVertexArrayAttribFormat(vaoId, 0, 2, GL_FLOAT, GL_TRUE, offsetof(OglVertexInfo, x));
    glVertexArrayAttribBinding(vaoId, 0, vboBindingPoint);

    glEnableVertexArrayAttrib(vaoId, 1);
    glVertexArrayAttribFormat(vaoId, 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(OglVertexInfo, r));
    glVertexArrayAttribBinding(vaoId, 1, vboBindingPoint);
}

//======================================================================================================================
auto OglVertexBuffer::getVboId() const -> VboRawId
{
    return _buffer.getBufferRawId();
}

//======================================================================================================================
TypedOglBuffer<OglVertexInfo>& OglVertexBuffer::getUnderlyingBuffer()
{
    return _buffer;
}
