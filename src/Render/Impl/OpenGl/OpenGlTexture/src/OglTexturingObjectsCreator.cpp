#include "OglTexturingObjectsCreator.h"

#include "OglTextureHandles.h"
#include "OglTextureSampler.h"

#include <OpenGlTexture/OpenGlTexture.h>

//======================================================================================================================
using namespace texture;
using namespace opengl_texture;

//======================================================================================================================
OglTexturingObjectsCreator::OglTexturingObjectsCreator(OglTextureHandles& texHandles)
    : _textureHandles(texHandles)
{
}

//======================================================================================================================
uptr<Texture> OglTexturingObjectsCreator::createTexture(const TextureData& textureData)
{
    return makeUPtr<OpenGlTexture>(textureData, _textureHandles);
}

//======================================================================================================================
uptr<TextureSampler> OglTexturingObjectsCreator::createSampler(const TextureSamplingParameters& samplingParams)
{
    return makeUPtr<OglTextureSampler>(samplingParams, _textureHandles);
}
