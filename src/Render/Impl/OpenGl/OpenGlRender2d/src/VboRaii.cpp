#include "VboRaii.h"

#include <Common/String.h>
// TODO: single cpp for avoiding many inclusions of this header?
#include <OpenGlApi/OpenGlApi.h>

#include <cassert>
#include <stdexcept>
#include <type_traits>
#include <utility>

//======================================================================================================================
using opengl_render_2d::VboRaii;

//======================================================================================================================
void VboRaii::_staticAssertsOnTypedefs() noexcept
{
    static_assert(std::is_same_v<BufferSizeInBytes, GLsizeiptr>);
    static_assert(std::is_same_v<BufferRawId, GLuint>);
}

//======================================================================================================================
VboRaii::VboRaii(const BufferSizeInBytes bufferSizeInBytes, const MapOnCreation mapOnCreation)
    : _currentSizeInBytes(bufferSizeInBytes)
{
    glCreateBuffers(1, &_bufferId);

    const auto bufferUsageFlags = [&] -> uint32 {
        if (mapOnCreation)
            return GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

        return 0;
    }();
    glNamedBufferStorage(_bufferId, _currentSizeInBytes, nullptr, bufferUsageFlags);
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        throw std::runtime_error(strFormat("Failed to glNamedBufferStorage(). OGL Error code: {}",
                                           lastGlError));

    if (mapOnCreation) {
        _bufferMappingPtr = glMapNamedBufferRange(_bufferId, 0, _currentSizeInBytes, bufferUsageFlags);
        if (!*_bufferMappingPtr)
            throw std::runtime_error(strFormat("Failed to map vbo(id={}) for {} bytes. OGL Error code: {}",
                                               _bufferId,
                                               _currentSizeInBytes,
                                               glGetError()));
    }
}

//======================================================================================================================
VboRaii::VboRaii(VboRaii&& other)
    : _currentSizeInBytes(other._currentSizeInBytes)
    , _bufferId(other._bufferId)
    , _bufferMappingPtr(std::move(other._bufferMappingPtr))
{
    other._currentSizeInBytes = 0;
    other._bufferId = 0;
    other._bufferMappingPtr = {};
}

//======================================================================================================================
VboRaii& VboRaii::operator=(VboRaii&& other)
{
    _release();

    _currentSizeInBytes = other._currentSizeInBytes;
    _bufferId = other._bufferId;
    _bufferMappingPtr = std::move(other._bufferMappingPtr);

    other._currentSizeInBytes = 0;
    other._bufferId = 0;
    other._bufferMappingPtr = {};

    return *this;
}

//======================================================================================================================
VboRaii::~VboRaii()
{
    _release();
}

//======================================================================================================================
auto VboRaii::getVboSizeInBytes() const -> BufferSizeInBytes
{
    return _currentSizeInBytes;
}

//======================================================================================================================
auto VboRaii::getVboId() const -> BufferRawId
{
    return _bufferId;
}

//======================================================================================================================
Optional<void*> VboRaii::getVboMappingPtr() const
{
    return _bufferMappingPtr;
}

//======================================================================================================================
void VboRaii::_release()
{
    const auto isBufferMapped = _bufferMappingPtr.has_value();
    assert(!_bufferMappingPtr || _bufferMappingPtr.value());

    if (!_bufferId) {
        assert(!isBufferMapped);
        return;
    }

    if (isBufferMapped)
        glUnmapNamedBuffer(_bufferId);

    glDeleteBuffers(1, &_bufferId);

    _bufferMappingPtr = {};
    _bufferId = 0;
    _currentSizeInBytes = 0;
}
