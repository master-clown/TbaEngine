#include <SdlRenderer/SdlRenderer.h>

#include <SdlRender2d/SdlRenderer2d.h>
#include <SdlWinsys/SdlWindow.h>

#include <cassert>

//==================================================================================================================
using sdl_renderer::SdlRenderer;

//==================================================================================================================
SdlRenderer::SdlRenderer(renderer_context::RendererContextRaii rendererContext)
    : render::Renderer(std::move(rendererContext))
    , _sdlWindow([&] -> sdl_winsys::SdlWindow& {
        auto* targetWindow = getRendererContext().getTargetWindow();
        assert(targetWindow);
        assert(dynamic_cast<sdl_winsys::SdlWindow*>(targetWindow) &&
               "SdlRenderer can be used only on SDL windows");

        return static_cast<sdl_winsys::SdlWindow&>(*targetWindow);
    }())
    , _renderer2d(makeUPtr<sdl_render_2d::SdlRenderer2d>(_sdlWindow))
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

//==================================================================================================================
texture::TextureCreator& SdlRenderer::getTextureCreator()
{
    throw std::logic_error("Not implemented");
}
