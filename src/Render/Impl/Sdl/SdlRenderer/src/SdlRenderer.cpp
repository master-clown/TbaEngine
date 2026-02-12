#include <SdlRenderer/SdlRenderer.h>

#include <SdlRender2d/SdlRenderer2d.h>

#include <cassert>

//==================================================================================================================
using sdl_render::SdlRenderer;

//==================================================================================================================
SdlRenderer::SdlRenderer(sdl_winsys::SdlWindow& sdlWindow, renderer_context::RendererContextRaii rendererContext)
    : render::Renderer(std::move(rendererContext))
    , _renderer2d(makeUPtr<SdlRenderer2d>(sdlWindow))
{
    assert(getRendererContext().getRendererType() == renderer_context::RendererType::Sdl);
}

//==================================================================================================================
SdlRenderer::~SdlRenderer() = default;

//==================================================================================================================
void SdlRenderer::clear(const content::Color& color)
{
    get2dRenderer().clear(color);
}

//==================================================================================================================
void SdlRenderer::finalizeRender()
{
    get2dRenderer().finalizeRender();
}

//==================================================================================================================
render_2d::Renderer& SdlRenderer::get2dRenderer()
{
    assert(_renderer2d);
    return *_renderer2d;
}

//==================================================================================================================
render_3d::Renderer& SdlRenderer::get3dRenderer()
{
    throw std::logic_error("Not implemented");
}
