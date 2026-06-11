#include "OglTextureHandles.h"

#include "OglTextureSampler.h"

#include <OpenGlApi/ErrorCheck.h>
#include <OpenGlApi/OpenGlApi.h>

#include <cassert>

//======================================================================================================================
using opengl_texture::OglTextureHandleRaii;
using opengl_texture::OglTextureHandles;
using opengl_texture::OglTextureSampler;
using opengl_texture::OpenGlTextureHandle;

//======================================================================================================================
OglTextureHandles::OglTextureHandles() = default;

//======================================================================================================================
OglTextureHandles::~OglTextureHandles()
{
    setSamplerForAllTextures(nullptr);
}

//======================================================================================================================
void OglTextureHandles::addForTexture(const OpenGlTextureId textureId)
{
    [[maybe_unused]] const auto [it, didEmplace] = _handles.emplace(textureId, _makeHandle(textureId));
    assert(didEmplace);
}

//======================================================================================================================
void OglTextureHandles::removeForTexture(const OpenGlTextureId textureId)
{
    _handles.erase(textureId);
}

//======================================================================================================================
void OglTextureHandles::setSamplerForAllTextures(OglTextureSamplerPtrOrNull sampler)
{
    _currentlyActiveSampler = sampler;

    for (auto& [textureId, textureHandle] : _handles)
        _handles.insert_or_assign(textureId, _makeHandle(textureId));
}

//======================================================================================================================
OpenGlTextureHandle OglTextureHandles::getHandle(const OpenGlTextureId textureId) const
{
    const auto it = _handles.find(textureId);
    assert(it != _handles.cend());

    if (it->second.getHandle() == noneOpenGlTextureHandle)
        throw std::runtime_error(
            strFormat("OpenGL texture handle is not initialized for oglTextureHandle={}", textureId));

    return it->second.getHandle();
}

//======================================================================================================================
auto OglTextureHandles::_getCurrentlyActiveSampler() const noexcept -> OglTextureSamplerPtrOrNull
{
    return _currentlyActiveSampler;
}

//======================================================================================================================
OglTextureHandleRaii OglTextureHandles::_makeHandle(const OpenGlTextureId textureId) const
{
    if (!_currentlyActiveSampler)
        return OglTextureHandleRaii{noneOpenGlTextureHandle};

    const auto samplerId = _currentlyActiveSampler->getOglSamplerId();

    const auto handle = glGetTextureSamplerHandleARB(textureId, samplerId);
    opengl_api::checkOperationSuccess(strFormat("glGetTextureSamplerHandleARB(texId={}, samplerId={})",
                                                textureId,
                                                samplerId));
    assert(handle != 0);

    return OglTextureHandleRaii{handle};
}
