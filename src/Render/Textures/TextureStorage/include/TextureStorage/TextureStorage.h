#pragma once

#include <TextureStorage/TextureId.h>

#include <Common/Memory.h>
#include <Common/Stl/HashMap.h>

#include <atomic>

//======================================================================================================================
namespace texture {
    class Texture;
    struct TextureData;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage final {
    public:
        TextureStorage();
        ~TextureStorage();

        //--------------------------------------------------------------------------------------------------------------
        void clear();
        TextureId add(uptr<texture::Texture>);

        texture::Texture& get(TextureId);
        const texture::Texture& get(TextureId) const;

    private:
        using _TextureRawId = TextureId::Id;

        HashMap<_TextureRawId, uptr<texture::Texture>> _textures;

        //--------------------------------------------------------------------------------------------------------------
        static std::atomic<_TextureRawId> _nextId;
    };
}
