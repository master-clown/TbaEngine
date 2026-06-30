#include <SdlTexture/SdlTexturingMgr.h>

#include "SdlTextureSampler.h"
#include "SdlTexturingObjectsCreator.h"

#include <cassert>

//======================================================================================================================
using sdl_texture::SdlTexturingMgr;

//======================================================================================================================
SdlTexturingMgr::SdlTexturingMgr()
    : _textureHandles(makeUPtr<SdlTextureHandles>())
    , _texturingObjectsCreator(makeUPtr<SdlTexturingObjectsCreator>(*_textureHandles))
{
}

//======================================================================================================================
SdlTexturingMgr::~SdlTexturingMgr() = default;

//======================================================================================================================
texture::TexturingObjectsCreator& SdlTexturingMgr::getTexturingObjectsCreator()
{
    assert(_texturingObjectsCreator);
    return *_texturingObjectsCreator;
}

//======================================================================================================================
void SdlTexturingMgr::_setCurrentTextureSampler(TextureSamplerOrNull textureSampler)
{
    if (!textureSampler) {
        _textureHandles->setSamplerForAllTextures(nullptr);
        return;
    }

    assert(dynamic_cast<SdlTextureSampler*>(textureSampler));
    auto& oglTextureSampler = static_cast<SdlTextureSampler&>(*textureSampler);
    _textureHandles->setSamplerForAllTextures(&oglTextureSampler);
}
