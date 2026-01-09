#include <SdlRenderer/SdlRenderer.h>

#include <SdlRender2d/SdlRenderer2d.h>

#include <cassert>

//==================================================================================================================
sdl_render::SdlRenderer::SdlRenderer(sdl_winsys::SdlWindow& sdlWindow)
    : _renderer2d(makeUPtr<sdl_render::SdlRenderer2d>(sdlWindow))
{
}

//==================================================================================================================
sdl_render::SdlRenderer::~SdlRenderer() = default;

//==================================================================================================================
void sdl_render::SdlRenderer::clear(const content::Color& color)
{
    get2dRenderer().clear(color);
}

//==================================================================================================================
void sdl_render::SdlRenderer::finalizeRender()
{
    get2dRenderer().finalizeRender();
}

//==================================================================================================================
render_2d::Renderer& sdl_render::SdlRenderer::get2dRenderer()
{
    assert(_renderer2d);
    return *_renderer2d;
}

//==================================================================================================================
render_3d::Renderer& sdl_render::SdlRenderer::get3dRenderer()
{
    throw std::logic_error("Not implemented");
}
