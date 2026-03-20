#include "OglBuffer.h"

#include <Common/String.h>
// TODO: single cpp for avoiding many inclusions of this header?
#include <OpenGlApi/OpenGlApi.h>

#include <cassert>
#include <stdexcept>
#include <type_traits>
#include <utility>

//======================================================================================================================
using opengl_render_2d::OglBuffer;

//======================================================================================================================
void OglBuffer::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<BufferRawId, GLuint>);
    static_assert(std::is_same_v<BufferSize, GLsizeiptr>);
}

//======================================================================================================================
OglBuffer::OglBuffer()
{
    glCreateBuffers(1, &_vboId);

    constexpr auto bufferUsageFlags =
        GL_MAP_WRITE_BIT |
        GL_MAP_PERSISTENT_BIT |
        GL_MAP_COHERENT_BIT;
    glNamedBufferStorage(_vboId, _currentAllocSizeInBytes, nullptr, bufferUsageFlags);
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        throw std::runtime_error(strFormat("Failed to glNamedBufferStorage(). OGL Error code: {}",
                                           lastGlError));

    _bufferMappingPtr = glMapNamedBufferRange(_vboId, 0, _currentAllocSizeInBytes, bufferUsageFlags);
    if (!_bufferMappingPtr)
        throw std::runtime_error(strFormat("Failed to map vbo(id={}) for {} bytes. OGL Error code: {}",
                                           _vboId,
                                           _currentAllocSizeInBytes,
                                           glGetError()));

    assert(_bufferMappingPtr);
}

//======================================================================================================================
OglBuffer::~OglBuffer()
{
    glUnmapNamedBuffer(_vboId);
    glDeleteBuffers(1, &_vboId);
}

//======================================================================================================================
size_t OglBuffer::getCurrentAllocSizeInBytes() const
{
    return static_cast<size_t>(_currentAllocSizeInBytes);
}

//======================================================================================================================
auto OglBuffer::getBufferRawId() const -> BufferRawId
{
    return _vboId;
}

//======================================================================================================================
void OglBuffer::useBuffer(const MaxRequiredOffsetInBytes maxRequiredOffsetInBytes,
                          const std::function<void(const NonPersistentBufferPtr bufferPtr)>& action)
{
    if (_currentAllocSizeInBytes < maxRequiredOffsetInBytes) {
        const size_t newChunksCount = maxRequiredOffsetInBytes / _baseChunkSizeInBytes + 1;
        const auto newSizeInBytes = newChunksCount * _baseChunkSizeInBytes;
        _extendBuffer(newSizeInBytes);
    }

    action({.ptr = _bufferMappingPtr});
}

//======================================================================================================================
void OglBuffer::_extendBuffer(const BufferSize newSize)
{
    // TODO: implement me
    std::unreachable();
}
