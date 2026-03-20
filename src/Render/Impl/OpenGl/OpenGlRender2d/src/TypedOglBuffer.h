#pragma once

#include "OglBuffer.h"

#include <concepts>

//======================================================================================================================
namespace opengl_render_2d {
    //==================================================================================================================
    template <class T>
    concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

    //==================================================================================================================
    template <TriviallyCopyable BufferItem>
    class TypedOglBuffer final : public OglBuffer {
    public:
        using NewBufferItemIndex = size_t;

        void clear();
        NewBufferItemIndex append(const BufferItem&);

        struct ItemUnsafePtr final {
            BufferItem* ptr;
        };

        void modify(const size_t itemIndex,
                    const std::function<void(const ItemUnsafePtr)>& modifyItem);

        //--------------------------------------------------------------------------------------------------------------
        size_t getItemCount() const;
        size_t getUsedBytesCount() const;

    private:
        static constexpr auto _itemSizeInBytes = sizeof(BufferItem);

        size_t _itemCount = 0;
    };
}
