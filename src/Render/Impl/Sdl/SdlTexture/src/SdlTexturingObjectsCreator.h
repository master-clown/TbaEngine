#pragma once

#include <Common/Memory.h>
#include <Texture/TexturingObjectsCreator.h>

//======================================================================================================================
struct SDL_Renderer;

//======================================================================================================================
namespace sdl_texture {
    class SdlTexturingObjectsCreator final : public texture::TexturingObjectsCreator {
    public:
        explicit SdlTexturingObjectsCreator(SDL_Renderer&);

        uptr<texture::Texture> createTexture(const texture::TextureData&) override;
        uptr<texture::TextureSampler> createSampler(const texture::TextureSamplingParameters&) override;

    private:
        SDL_Renderer& _sdlRenderer;
    };
}
