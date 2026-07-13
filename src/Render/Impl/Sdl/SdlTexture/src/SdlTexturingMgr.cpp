#include <SdlTexture/SdlTexturingMgr.h>

#include "SdlTextureSampling.h"
#include "SdlTexturingObjectsCreator.h"

#include "SDL3/SDL_render.h"

#include <cassert>

//======================================================================================================================
using sdl_texture::SdlTexturingMgr;

//======================================================================================================================
SdlTexturingMgr::SdlTexturingMgr() = default;

//======================================================================================================================
SdlTexturingMgr::~SdlTexturingMgr() = default;

//======================================================================================================================
texture::TexturingObjectsCreator& SdlTexturingMgr::getTexturingObjectsCreator()
{
    if (!_texturingObjectsCreator) {
        assert(_sdlRenderer);
        _texturingObjectsCreator = makeUPtr<SdlTexturingObjectsCreator>(*_sdlRenderer);
    }

    return *_texturingObjectsCreator;
}

//======================================================================================================================
void SdlTexturingMgr::setSdlRenderer(SDL_Renderer& sdlRenderer)
{
    if (_sdlRenderer)
        throw std::logic_error("SDL Renderer is already set for 'SdlTexturingMgr'");

    _sdlRenderer = &sdlRenderer;
}

//======================================================================================================================
void SdlTexturingMgr::_setCurrentTextureSampler(TextureSamplerOrNull textureSampler)
{
    if (!textureSampler)
        return;

    assert(_sdlRenderer);

    assert(dynamic_cast<SdlTextureSampling*>(textureSampler));
    auto& sdlTextureSampler = static_cast<SdlTextureSampling&>(*textureSampler);
    sdlTextureSampler.activateFor(*_sdlRenderer);
}
