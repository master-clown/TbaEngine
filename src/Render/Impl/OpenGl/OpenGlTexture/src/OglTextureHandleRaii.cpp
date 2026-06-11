#include "OglTextureHandleRaii.h"

#include <OpenGlApi/ErrorCheck.h>
#include <OpenGlApi/OpenGlApi.h>

#include <cassert>

//======================================================================================================================
using opengl_texture::OglTextureHandleRaii;
using opengl_texture::OpenGlTextureHandle;

//======================================================================================================================
OglTextureHandleRaii::OglTextureHandleRaii(OpenGlTextureHandle handle)
    : _handle(OpenGlTextureHandle{handle})
{
    if (_handle.getUnderlying() == 0)
        return;

    glMakeTextureHandleResidentARB(_handle);
    opengl_api::checkOperationSuccess(strFormat("glMakeTextureHandleResidentARB(handle={})", _handle.getUnderlying()));
}

//======================================================================================================================
OglTextureHandleRaii::OglTextureHandleRaii(OglTextureHandleRaii&& other)
    : _handle(other.getHandle())
{
    other._handle.getUnderlying() = noneOpenGlTextureHandle;
}

//======================================================================================================================
OglTextureHandleRaii& OglTextureHandleRaii::operator=(OglTextureHandleRaii&& other)
{
    _handle.getUnderlying() = other._handle;
    other._handle.getUnderlying() = noneOpenGlTextureHandle;

    return *this;
}

//======================================================================================================================
OpenGlTextureHandle OglTextureHandleRaii::getHandle() const
{
    return _handle;
}

//======================================================================================================================
void OglTextureHandleRaii::OnHandleDestruction::operator()(const OpenGlTextureHandle& textureHandle) const noexcept
{
    if (textureHandle != noneOpenGlTextureHandle) {
        glMakeTextureHandleNonResidentARB(textureHandle);
        opengl_api::logOnOperationFailure(strFormat("glMakeTextureHandleNonResidentARB(handle={})", textureHandle));
    }
}
