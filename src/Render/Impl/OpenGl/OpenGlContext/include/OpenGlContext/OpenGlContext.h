#pragma once

#include <Common/Integers.h>
#include <Common/Memory.h>
#include <RendererContext/RendererContext.h>

//======================================================================================================================
namespace opengl_api {
    class GpuOperationsCompletedEvent;
}

//======================================================================================================================
namespace opengl_context {
    //==================================================================================================================
    class OpenGlContext : public renderer_context::RendererContext {
    public:
        using OpenGlFunctionsLoader = void* (*)(const char* functionName);
        explicit OpenGlContext(OpenGlFunctionsLoader);
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

        //--------------------------------------------------------------------------------------------------------------
        OpenGlFunctionsLoader getOpenGlFunctionsLoader() const noexcept;

        //--------------------------------------------------------------------------------------------------------------
        opengl_api::GpuOperationsCompletedEvent& getGpuOperationsCompletedEvent();

    private:
        OpenGlFunctionsLoader _openGlFunctionsLoader = nullptr;
        uptr<opengl_api::GpuOperationsCompletedEvent> _gpuOperationsCompletedEvent;
    };
}
