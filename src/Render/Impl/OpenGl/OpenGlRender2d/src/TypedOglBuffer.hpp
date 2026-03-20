#pragma once

#include "TypedOglBuffer.h"

#include <cassert>
#include <cstring>

//======================================================================================================================
template <opengl_render_2d::TriviallyCopyable BufferItem>
void opengl_render_2d::TypedOglBuffer<BufferItem>::clear()
{
    _itemCount = 0;
}

//======================================================================================================================
template <opengl_render_2d::TriviallyCopyable BufferItem>
auto opengl_render_2d::TypedOglBuffer<BufferItem>::append(const BufferItem& item) -> NewBufferItemIndex
{
    const auto maxRequiredOffset = _itemSizeInBytes * (_itemCount + 1) - 1;
    useBuffer(maxRequiredOffset, [&](OglBuffer::NonPersistentBufferPtr buffer) {
        assert(buffer.ptr);
        const auto dstPtr = static_cast<BufferItem*>(buffer.ptr) + _itemCount;
        std::memcpy(static_cast<void*>(dstPtr),
                    static_cast<const void*>(&item),
                    _itemSizeInBytes);
    });

    return _itemCount++;
}

//======================================================================================================================
template <opengl_render_2d::TriviallyCopyable BufferItem>
void opengl_render_2d::TypedOglBuffer<BufferItem>::modify(const size_t itemIndex,
                                                          const std::function<void(const ItemUnsafePtr)>& modifyItem)
{
    assert(itemIndex < _itemCount);

    const auto maxRequiredOffset = itemIndex * _itemCount + _itemSizeInBytes - 1;
    useBuffer(maxRequiredOffset,
              [itemIndex, &modifyItem](const OglBuffer::NonPersistentBufferPtr buffer) {
                  assert(buffer.ptr);

                  modifyItem({
                      .ptr = static_cast<BufferItem*>(buffer.ptr) + itemIndex,
                  });
              });
}

//======================================================================================================================
template <opengl_render_2d::TriviallyCopyable BufferItem>
size_t opengl_render_2d::TypedOglBuffer<BufferItem>::getItemCount() const
{
    return _itemCount;
}

//======================================================================================================================
template <opengl_render_2d::TriviallyCopyable BufferItem>
size_t opengl_render_2d::TypedOglBuffer<BufferItem>::getUsedBytesCount() const
{
    return getItemCount() * _itemSizeInBytes;
}
