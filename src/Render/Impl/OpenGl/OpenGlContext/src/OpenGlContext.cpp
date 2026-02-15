#include <OpenGlContext/OpenGlContext.h>

#include <cassert>

//======================================================================================================================
using opengl_context::OpenGlContext;

//======================================================================================================================
OpenGlContext::OpenGlContext(OpenGlFunctionsLoader openGlFunctionsLoader)
    : _openGlFunctionsLoader(openGlFunctionsLoader)
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
