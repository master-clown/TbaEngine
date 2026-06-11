#pragma once

#include "OglTextureHandleRaii.h"

#include <OpenGlTexture/OpenGlTextureHandle.h>
#include <OpenGlTexture/OpenGlTextureId.h>

#include <Common/Stl/HashMap.h>

//======================================================================================================================
namespace opengl_texture {
    class OglTextureSampler;
}

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandles final {
    public:
        OglTextureHandles();
        ~OglTextureHandles();

        //--------------------------------------------------------------------------------------------------------------
        void addForTexture(OpenGlTextureId);
        void removeForTexture(OpenGlTextureId);

        using OglTextureSamplerPtrOrNull = const OglTextureSampler*;
        void setSamplerForAllTextures(OglTextureSamplerPtrOrNull);

        //--------------------------------------------------------------------------------------------------------------
        OpenGlTextureHandle getHandle(OpenGlTextureId) const;

    private:
        friend OglTextureSampler;
        OglTextureSamplerPtrOrNull _getCurrentlyActiveSampler() const noexcept;

    private:
        OglTextureHandleRaii _makeHandle(OpenGlTextureId) const;

        //--------------------------------------------------------------------------------------------------------------
        OglTextureSamplerPtrOrNull _currentlyActiveSampler = nullptr;
        HashMap<OpenGlTextureId, OglTextureHandleRaii> _handles;
    };
}
