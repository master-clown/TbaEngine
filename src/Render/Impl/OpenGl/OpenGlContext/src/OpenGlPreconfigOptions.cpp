#include <OpenGlContext/OpenGlPreconfigOptions.h>

//======================================================================================================================
using opengl_context::OpenGlPreconfigOptions;

//======================================================================================================================
renderer_context::RendererType OpenGlPreconfigOptions::getRendererType() const
{
    return renderer_context::RendererType::OpenGl;
}
