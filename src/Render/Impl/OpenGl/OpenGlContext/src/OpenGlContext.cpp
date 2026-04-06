#include <OpenGlContext/OpenGlContext.h>

#include <OpenGlApi/GpuOperationsCompletedEvent.h>

#include <cassert>

//======================================================================================================================
using opengl_context::OpenGlContext;

//======================================================================================================================
OpenGlContext::OpenGlContext(OpenGlFunctionsLoader openGlFunctionsLoader)
    : _openGlFunctionsLoader(openGlFunctionsLoader)
    , _gpuOperationsCompletedEvent(makeUPtr<opengl_api::GpuOperationsCompletedEvent>())
{
    assert(_openGlFunctionsLoader);
}

//======================================================================================================================
OpenGlContext::~OpenGlContext() = default;

//======================================================================================================================
renderer_context::RendererType OpenGlContext::getRendererType() const
{
    return renderer_context::RendererType::OpenGl;
}

//======================================================================================================================
auto OpenGlContext::getOpenGlFunctionsLoader() const noexcept -> OpenGlFunctionsLoader
{
    return _openGlFunctionsLoader;
}

//======================================================================================================================
opengl_api::GpuOperationsCompletedEvent& OpenGlContext::getGpuOperationsCompletedEvent()
{
    assert(_gpuOperationsCompletedEvent);
    return *_gpuOperationsCompletedEvent;
}
