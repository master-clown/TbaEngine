#pragma once

#include <Common/Integers.h>
#include <Common/Memory.h>
#include <RendererContext/RendererContext.h>

//======================================================================================================================
namespace opengl_context {
    class OpenGlLibraryRaii;
}

//======================================================================================================================
namespace opengl_context {
    //==================================================================================================================
    class OpenGlContext : public renderer_context::RendererContext {
    public:
        using LoadOpenGlFunction = void* (*)(const char* functionName);
        explicit OpenGlContext(LoadOpenGlFunction);
        ~OpenGlContext();

        //--------------------------------------------------------------------------------------------------------------
        renderer_context::RendererType getRendererType() const override final;

        //--------------------------------------------------------------------------------------------------------------
        virtual void makeGlContextAsCurrent() = 0;

        //--------------------------------------------------------------------------------------------------------------
        virtual void setSwapInterval(int) = 0; // TODO: better type for the argument
        virtual void swapBuffers() = 0;

        //--------------------------------------------------------------------------------------------------------------
        // GL attributes

        virtual void setGlMajorVersion(uint32) = 0;
        virtual void setGlMinorVersion(uint32) = 0;

        enum class GlProfile {
            Core,
            Compatibility,
        };

        virtual void setGlProfile(GlProfile) = 0;

    private:
        uptr<OpenGlLibraryRaii> _openGlLibraryRaii;
    };
}
