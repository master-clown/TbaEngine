#include <OpenGlTexture/OpenGlTexturingMgr.h>

#include "OglTextureHandles.h"
#include "OglTextureSampler.h"
#include "OglTexturingObjectsCreator.h"

#include <cassert>

//======================================================================================================================
using opengl_texture::OpenGlTexturingMgr;

//======================================================================================================================
OpenGlTexturingMgr::OpenGlTexturingMgr()
    : _textureHandles(makeUPtr<OglTextureHandles>())
    , _texturingObjectsCreator(makeUPtr<OglTexturingObjectsCreator>(*_textureHandles))
{
}

//======================================================================================================================
OpenGlTexturingMgr::~OpenGlTexturingMgr() = default;

//======================================================================================================================
texture::TexturingObjectsCreator& OpenGlTexturingMgr::getTexturingObjectsCreator()
{
    assert(_texturingObjectsCreator);
    return *_texturingObjectsCreator;
}

//======================================================================================================================
void OpenGlTexturingMgr::_setCurrentTextureSampler(TextureSamplerOrNull textureSampler)
{
    if (!textureSampler) {
        _textureHandles->setSamplerForAllTextures(nullptr);
        return;
    }

    assert(dynamic_cast<OglTextureSampler*>(textureSampler));
    auto& oglTextureSampler = static_cast<OglTextureSampler&>(*textureSampler);
    _textureHandles->setSamplerForAllTextures(&oglTextureSampler);
}
