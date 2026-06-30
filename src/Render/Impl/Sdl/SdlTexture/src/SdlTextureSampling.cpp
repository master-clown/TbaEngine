#include "SdlTextureSampling.h"

#include <Common/String.h>
#include <Logger/BasicLogging.h>

#include <SDL3/SDL_render.h>

#include <stdexcept>
#include <type_traits>

//======================================================================================================================
using sdl_texture::SdlTextureSampling;

//======================================================================================================================
namespace {
    using SdlAddressMode = SDL_TextureAddressMode;
    constexpr SdlAddressMode convertAddressMode(texture::TextureSamplingParameters::AddressMode);

    using SdlFiltering = SDL_ScaleMode;
    constexpr SdlFiltering convertFiltering(texture::TextureSamplingParameters::Filtering) noexcept;
}

//======================================================================================================================
SdlTextureSampling::SdlTextureSampling(const texture::TextureSamplingParameters& params)
    : _samplingParameters(params)
{
    if (params.minifyNeighborFiltering != params.magnifyNeighborFiltering)
        LOG_ALWAYS(
            "SDL supports only a single filtering mode. "
            "Choosing filtering mode from minifyNeighborFiltering={}",
            params.minifyNeighborFiltering);

    // TODO: Inform that mipmapping is not supported in SDL_render (make minifyMipmapFiltering as Optional)
}

//======================================================================================================================
void SdlTextureSampling::activateFor(SDL_Renderer& sdlRenderer)
{
    {
        const auto uAddressMode = convertAddressMode(_samplingParameters.addressModeU);
        const auto vAddressMode = convertAddressMode(_samplingParameters.addressModeV);
        if (!SDL_SetRenderTextureAddressMode(&sdlRenderer, uAddressMode, vAddressMode))
            throw std::runtime_error(strFormat("Failed to SDL_SetRenderTextureAddressMode(uMode={}, vMode={}): {}",
                                               _samplingParameters.addressModeU,
                                               _samplingParameters.addressModeV,
                                               SDL_GetError()));
    }

    {
        const auto sdlFilterMode = convertFiltering(_samplingParameters.minifyNeighborFiltering);
        if (!SDL_SetDefaultTextureScaleMode(&sdlRenderer, sdlFilterMode))
            throw std::runtime_error(strFormat("Failed to SDL_SetDefaultTextureScaleMode(mode={}): {}",
                                               _samplingParameters.minifyNeighborFiltering,
                                               SDL_GetError()));
    }
}

//======================================================================================================================
namespace {
    //==================================================================================================================
    constexpr SdlAddressMode convertAddressMode(const texture::TextureSamplingParameters::AddressMode mode)
    {
        using En = texture::TextureSamplingParameters::AddressMode;

        switch (mode) {
        case En::Clamp: return SDL_TEXTURE_ADDRESS_CLAMP;
        case En::Repeat: return SDL_TEXTURE_ADDRESS_WRAP;
        }

        throw std::runtime_error(strFormat("SDL does not support {}", str(mode)));
    }

    //==================================================================================================================
    constexpr SdlFiltering convertFiltering(const texture::TextureSamplingParameters::Filtering filtering) noexcept
    {
        using En = texture::TextureSamplingParameters::Filtering;

        switch (mode) {
        case En::Nearest: return SDL_SCALEMODE_NEAREST;
        case En::Linear: return SDL_SCALEMODE_LINEAR;
        }

        std::unreachable();
    }
}
