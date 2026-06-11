#include <OpenGlTexture/OpenGlTexturingObjectsCreator.h>

#include "OglTextureHandles.h"
#include "OglTextureSampler.h"

#include <OpenGlTexture/OpenGlTexture.h>

//======================================================================================================================
using namespace texture;
using namespace opengl_texture;

//======================================================================================================================
OpenGlTexturingObjectsCreator::OpenGlTexturingObjectsCreator()
    : _textureHandles(makeUPtr<OglTextureHandles>())
{
}

//======================================================================================================================
OpenGlTexturingObjectsCreator::~OpenGlTexturingObjectsCreator() = default;

//======================================================================================================================
uptr<Texture> OpenGlTexturingObjectsCreator::createTexture(const TextureData& textureData)
{
    return makeUPtr<OpenGlTexture>(textureData, *_textureHandles);
}

//======================================================================================================================
uptr<TextureSampler> OpenGlTexturingObjectsCreator::createSampler(const TextureSamplingParameters& samplingParams)
{
    return makeUPtr<OglTextureSampler>(samplingParams, *_textureHandles);
}
