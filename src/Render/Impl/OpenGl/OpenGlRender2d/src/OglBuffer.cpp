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
OglBuffer::OglBuffer(BufferExtendedCallback bufferExtendedCallback)
    : _bufferExtendedCallback(std::move(bufferExtendedCallback))
    , _currentBuffer(
          [] {
              static constexpr auto defaultInitialSize = 1 * OglBuffer::_baseChunkSizeInBytes;

              return defaultInitialSize;
          }(),
          VboRaii::MapOnCreation{true})
{
}

//======================================================================================================================
OglBuffer::~OglBuffer() = default;

//======================================================================================================================
auto OglBuffer::getCurrentAllocSizeInBytes() const -> BufferSizeInBytes
{
    return _currentBuffer.getVboSizeInBytes();
}

//======================================================================================================================
auto OglBuffer::getBufferRawId() const -> BufferRawId
{
    return _currentBuffer.getVboId();
}

//======================================================================================================================
void OglBuffer::useBuffer(const MaxRequiredOffsetInBytes maxRequiredOffsetInBytes,
                          const std::function<void(const NonPersistentBufferPtr bufferPtr)>& action)
{
    if (_currentBuffer.getVboSizeInBytes() <= maxRequiredOffsetInBytes) {
        const size_t newChunksCount = maxRequiredOffsetInBytes / _baseChunkSizeInBytes + 1;
        const auto newSizeInBytes = newChunksCount * _baseChunkSizeInBytes;
        _extendBuffer(newSizeInBytes);

        _bufferExtendedCallback();
    }

    const auto currentBufferPtr = _currentBuffer.getVboMappingPtr().value_or(nullptr);
    assert(currentBufferPtr);

    action({.ptr = currentBufferPtr});
}

//======================================================================================================================
void OglBuffer::_extendBuffer(const BufferSizeInBytes newSize)
{
    VboRaii backupBuffer(_currentBuffer.getVboSizeInBytes());

    using ReadOffset = GLintptr;
    using WriteOffset = GLintptr;
    glCopyNamedBufferSubData(_currentBuffer.getVboId(),
                             backupBuffer.getVboId(),
                             ReadOffset{0},
                             WriteOffset{0},
                             _currentBuffer.getVboSizeInBytes());
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        throw std::runtime_error(strFormat("Failed to save backup by glCopyNamedBufferSubData(). OGL Error code: {}",
                                           lastGlError));

    _currentBuffer = VboRaii(newSize, VboRaii::MapOnCreation{true});

    glCopyNamedBufferSubData(backupBuffer.getVboId(),
                             _currentBuffer.getVboId(),
                             ReadOffset{0},
                             WriteOffset{0},
                             backupBuffer.getVboSizeInBytes());
    if (const auto lastGlError = glGetError(); lastGlError != GL_NO_ERROR)
        throw std::runtime_error(strFormat("Failed to load backup by glCopyNamedBufferSubData(). OGL Error code: {}",
                                           lastGlError));
}
