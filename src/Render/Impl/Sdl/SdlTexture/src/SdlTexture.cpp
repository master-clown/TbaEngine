#include <SdlTexture/SdlTexture.h>

#include <Common/NumericCast.hpp>
#include <Texture/TextureData.h>

#include <SDL3/SDL_render.h>

#include <cassert>
#include <utility>

//======================================================================================================================
using sdl_texture::SdlTexture;

//======================================================================================================================
namespace {
    constexpr SDL_PixelFormat sdlPixelFormatFromChannelCount(uint8) noexcept;
}

//======================================================================================================================
SdlTexture::SdlTexture(const texture::TextureData& textureData, SDL_Renderer& sdlRenderer)
    : _sdlTextureRaii([&] {
        const auto pixelFormat = sdlPixelFormatFromChannelCount(textureData.channelCount);
        auto* sdlTexture = SDL_CreateTexture(&sdlRenderer,
                                             pixelFormat,
                                             SDL_TEXTUREACCESS_STATIC,
                                             numericCast<int>(textureData.width),
                                             numericCast<int>(textureData.height));
        if (!sdlTexture)
            throw std::runtime_error(strFormat("Failed to create SDL_Texture: {}", SDL_GetError()));

        return sdlTexture;
    }())
{
    const SDL_Rect* updateWholeTextureHint = nullptr;
    const auto texturePitch = numericCast<int>(textureData.channelCount * textureData.width);
    if (!SDL_UpdateTexture(_sdlTextureRaii, updateWholeTextureHint, &textureData.rawData[0], texturePitch))
        throw std::runtime_error(strFormat("Failed to create SDL_Texture: {}", SDL_GetError()));
}

//======================================================================================================================
SdlTexture::~SdlTexture() = default;

//======================================================================================================================
SDL_Texture& SdlTexture::getSdlTexture()
{
    return const_cast<SDL_Texture&>(static_cast<const SdlTexture&>(*this).getSdlTexture());
}

//======================================================================================================================
const SDL_Texture& SdlTexture::getSdlTexture() const
{
    assert(_sdlTextureRaii.getUnderlying());
    return _sdlTextureRaii.getUnderlying();
}

//======================================================================================================================
SdlTextureHandle SdlTexture::getSdlTextureHandle() const
{
    return _textureHandles.getHandle(_oglTextureId);
}

//======================================================================================================================
void SdlTexture::_OnSdlTextureDestruction::operator()(const SDL_Texture* sdlTexture) const noexcept
{
    SDL_DestroyTexture(sdlTexture);
}

//======================================================================================================================
namespace {
    constexpr SDL_PixelFormat sdlPixelFormatFromChannelCount(const uint8 channelCount) noexcept
    {
        assert(channelCount >= 3 && "At least 3 channels are supported by SDL");

        switch (channelCount) {
        case 3: return SDL_PIXELFORMAT_RGB24;
        case 4: return SDL_PIXELFORMAT_RGBA8888;
        default: break;
        };

        std::unreachable();
    }
}
