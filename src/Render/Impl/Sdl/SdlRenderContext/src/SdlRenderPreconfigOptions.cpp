#include <SdlRenderContext/SdlRenderPreconfigOptions.h>

//======================================================================================================================
using sdl_render_context::SdlRenderPreconfigOptions;

//======================================================================================================================
renderer_context::RendererType SdlRenderPreconfigOptions::getRendererType() const
{
    return renderer_context::RendererType::Sdl;
}
