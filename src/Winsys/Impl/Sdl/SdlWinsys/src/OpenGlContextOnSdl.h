#pragma once

#include <Common/Memory.h>
#include <OpenGlContext/OpenGlContext.h>

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow;
}

//======================================================================================================================
namespace sdl_winsys {
    //==================================================================================================================
    class OpenGlContextOnSdl final : public opengl_context::OpenGlContext {
    public:
        OpenGlContextOnSdl();
        ~OpenGlContextOnSdl();

        //--------------------------------------------------------------------------------------------------------------
        void initContext(winsys::Window&) override;
        void freeContext() override;
        void makeGlContextAsCurrent() override;

        //--------------------------------------------------------------------------------------------------------------
        void setSwapInterval(int) override;
        void swapBuffers() override;

        //--------------------------------------------------------------------------------------------------------------
        // GL attributes

        void setGlMajorVersion(uint32) override;
        void setGlMinorVersion(uint32) override;
        void setGlProfile(GlProfile) override;

    private:
        struct _Pimpl;

        uptr<_Pimpl> _pimpl;
        SdlWindow* _sdlWindow = nullptr;
    };
}
