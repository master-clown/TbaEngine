#include "OglVertexBuffer.h"

#include <OpenGlApi/ErrorCheck.h>
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
    : _vaoId(vaoId)
    , _buffer(OglBuffer::BufferExtendedCallback{[this] { _rebindVboToVao(); }})
{
    // TODO: assert(vao.isBinded());

    _rebindVboToVao();

    static constexpr GLuint vboBindingPoint = 0;

    glEnableVertexArrayAttrib(_vaoId, 0);
    glVertexArrayAttribFormat(_vaoId, 0, 2, GL_FLOAT, GL_TRUE, offsetof(OglVertexInfo, x));
    glVertexArrayAttribBinding(_vaoId, 0, vboBindingPoint);

    glEnableVertexArrayAttrib(_vaoId, 1);
    glVertexArrayAttribFormat(_vaoId, 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(OglVertexInfo, r));
    glVertexArrayAttribBinding(_vaoId, 1, vboBindingPoint);
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

//======================================================================================================================
void OglVertexBuffer::_rebindVboToVao() const
{
    static constexpr GLuint vboBindingPoint = 0;

    glVertexArrayVertexBuffer(_vaoId, vboBindingPoint, _buffer.getBufferRawId(), 0, sizeof(OglVertexInfo));
    opengl_api::checkOperationSuccess("OglVertexBuffer::_rebindVboToVao(): glVertexArrayVertexBuffer()");
}
