#pragma once

#include <Texture/TextureSampler.h>
#include <Texture/TextureSamplingParameters.h>

//======================================================================================================================
struct SDL_Renderer;

//======================================================================================================================
namespace sdl_texture {
    class SdlTextureSampling final : public texture::TextureSampler {
    public:
        explicit SdlTextureSampling(const texture::TextureSamplingParameters&);

        void activateFor(SDL_Renderer&) const;

    private:
        texture::TextureSamplingParameters _samplingParameters;
    };
}
