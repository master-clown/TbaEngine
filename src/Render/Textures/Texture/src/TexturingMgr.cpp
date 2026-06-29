#include <Texture/TexturingMgr.h>

//======================================================================================================================
using texture::TexturingMgr;

//======================================================================================================================
TexturingMgr::~TexturingMgr() = default;

//======================================================================================================================
void TexturingMgr::setCurrentTextureSampler(TextureSampler& sampler)
{
    _setCurrentTextureSampler(&sampler);
}

//======================================================================================================================
void TexturingMgr::setCurrentTextureSamplerToNone()
{
    _setCurrentTextureSampler(nullptr);
}
