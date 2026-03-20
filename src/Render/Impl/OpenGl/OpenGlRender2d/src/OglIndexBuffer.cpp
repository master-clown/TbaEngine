#include "OglIndexBuffer.h"

// TODO: single cpp for avoiding many inclusions of this header?
#include <OpenGlApi/OpenGlApi.h>

#include <type_traits>

//======================================================================================================================
using opengl_render_2d::OglIndexBuffer;
using opengl_render_2d::TypedOglBuffer;

//======================================================================================================================
void OglIndexBuffer::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<VaoId, GLuint>);
    static_assert(std::is_same_v<EboRawId, GLuint>);
    static_assert(std::is_same_v<OglIndexType, GLuint>);
}

//======================================================================================================================
OglIndexBuffer::OglIndexBuffer(const VaoId vaoId)
{
    // TODO: assert(vao.isBinded());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer.getBufferRawId());
}

//======================================================================================================================
auto OglIndexBuffer::getEboId() const -> EboRawId
{
    return _buffer.getBufferRawId();
}

//======================================================================================================================
auto OglIndexBuffer::getUnderlyingBuffer() -> TypedOglBuffer<Index>&
{
    return _buffer;
}

//======================================================================================================================
auto OglIndexBuffer::getUnderlyingBuffer() const -> const TypedOglBuffer<Index>&
{
    return _buffer;
}

//======================================================================================================================
auto OglIndexBuffer::getOglIndexType() -> OglIndexType
{
    return GL_UNSIGNED_INT;
}
