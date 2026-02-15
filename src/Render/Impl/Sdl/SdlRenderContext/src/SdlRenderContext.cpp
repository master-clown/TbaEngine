#include <SdlRenderContext/SdlRenderContext.h>

//======================================================================================================================
using sdl_render_context::SdlRenderContext;

//======================================================================================================================
renderer_context::RendererType SdlRenderContext::getRendererType() const
{
    return renderer_context::RendererType::Sdl;
}

//======================================================================================================================
void SdlRenderContext::_initContext()
{
}

//======================================================================================================================
void SdlRenderContext::_freeContext()
{
}
