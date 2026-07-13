#include "SdlTexturingObjectsCreator.h"

#include "SdlTextureSampling.h"

#include <SdlTexture/SdlTexture.h>

//======================================================================================================================
using namespace texture;
using namespace sdl_texture;

//======================================================================================================================
SdlTexturingObjectsCreator::SdlTexturingObjectsCreator(SDL_Renderer& sdlRenderer)
    : _sdlRenderer(sdlRenderer)
{
}

//======================================================================================================================
uptr<Texture> SdlTexturingObjectsCreator::createTexture(const TextureData& textureData)
{
    return makeUPtr<SdlTexture>(textureData, _sdlRenderer);
}

//======================================================================================================================
uptr<TextureSampler> SdlTexturingObjectsCreator::createSampler(const TextureSamplingParameters& samplingParams)
{
    return makeUPtr<SdlTextureSampling>(samplingParams);
}
