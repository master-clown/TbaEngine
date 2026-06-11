#pragma once

#include <OpenGlTexture/OpenGlTextureHandle.h>

#include <Common/RaiiWrapper.h>

//======================================================================================================================
namespace opengl_texture {
    class OglTextureHandleRaii final {
    public:
        explicit OglTextureHandleRaii(OpenGlTextureHandle);

        OglTextureHandleRaii(OglTextureHandleRaii&&);
        OglTextureHandleRaii& operator=(OglTextureHandleRaii&&);

        OglTextureHandleRaii(const OglTextureHandleRaii&) = delete;
        OglTextureHandleRaii& operator=(const OglTextureHandleRaii&) = delete;

        //----------------------------------------------------------------------------------------------------------
        OpenGlTextureHandle getHandle() const;

    private:
        struct OnHandleDestruction final {
            void operator()(const OpenGlTextureHandle&) const noexcept;
        };
        using _HandleRaii = RaiiWrapper<OpenGlTextureHandle, OnHandleDestruction{}>;

        _HandleRaii _handle;
    };
}

