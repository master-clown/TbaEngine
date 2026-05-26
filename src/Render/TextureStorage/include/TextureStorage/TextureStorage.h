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

        TextureId add(uptr<texture::Texture>);

        texture::Texture& get(TextureId);
        const texture::Texture& get(TextureId) const;

    private:
        HashMap<TextureId, uptr<texture::Texture>> _textures;
        std::atomic<TextureId> _nextId = 1;
    };
}
