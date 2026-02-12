#include <OpenGlContext/OpenGlContext.h>

//======================================================================================================================
using opengl_context::OpenGlContext;

//======================================================================================================================
renderer_context::RendererType OpenGlContext::getRendererType() const
{
    return renderer_context::RendererType::OpenGl;
}
