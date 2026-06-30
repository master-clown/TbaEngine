#pragma once

#include <Common/RaiiWrapper.h>
#include <Texture/Texture.h>

//======================================================================================================================
namespace texture {
    struct TextureData;
}

//======================================================================================================================
struct SDL_Renderer;
struct SDL_Texture;

//======================================================================================================================
namespace sdl_texture {
    class SdlTexture final : public texture::Texture {
    public:
        SdlTexture(const texture::TextureData&, SDL_Renderer&);
        ~SdlTexture();

        SDL_Texture& getSdlTexture();
        const SDL_Texture& getSdlTexture() const;

    private:
        struct _OnSdlTextureDestruction final {
            void operator()(const SDL_Texture*) const noexcept;
        };
        RaiiWrapper<SDL_Texture*, _OnSdlTextureDestruction{}> _sdlTextureRaii;
    };
}
