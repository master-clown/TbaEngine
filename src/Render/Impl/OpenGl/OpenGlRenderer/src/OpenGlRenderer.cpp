#include <OpenGlRenderer/OpenGlRenderer.h>

#include "OpenGlLibraryRaii.h"

#include <OpenGlApi/GpuOperationsCompletedEvent.h>
#include <OpenGlContext/OpenGlContext.h>
#include <OpenGlRender2d/OpenGlRenderer2d.h>

#include <cassert>

//==================================================================================================================
using opengl_renderer::OpenGlRenderer;

//==================================================================================================================
OpenGlRenderer::OpenGlRenderer(renderer_context::RendererContextRaii rendererContext)
    : render::Renderer(std::move(rendererContext))
    , _openGlContext([&] -> opengl_context::OpenGlContext& {
        auto& context = getRendererContext();
        assert(dynamic_cast<opengl_context::OpenGlContext*>(&context));

        return static_cast<opengl_context::OpenGlContext&>(context);
    }())
    , _openGlLibraryRaii(makeUPtr<OpenGlLibraryRaii>(OpenGlLibraryRaii::LibraryInitOptions{
          .openGlFunctionsLoader = _openGlContext.getOpenGlFunctionsLoader(),
      }))
    , _renderer2d(makeUPtr<opengl_render_2d::OpenGlRenderer2d>(_openGlContext))
{
    assert(getRendererContext().getRendererType() == renderer_context::RendererType::OpenGl);
}

//==================================================================================================================
OpenGlRenderer::~OpenGlRenderer() = default;

//==================================================================================================================
void OpenGlRenderer::clear(const content::Color& color)
{
    get2dRenderer().clear(color);
}

//==================================================================================================================
void OpenGlRenderer::finalizeRender()
{
    get2dRenderer().finalizeRender();

    _openGlContext.getGpuOperationsCompletedEvent().reset();
}

//==================================================================================================================
render_2d::Renderer& OpenGlRenderer::get2dRenderer()
{
    assert(_renderer2d);
    return *_renderer2d;
}

//==================================================================================================================
render_3d::Renderer& OpenGlRenderer::get3dRenderer()
{
    throw std::logic_error("Not implemented");
}

//==================================================================================================================
texture::TextureCreator& OpenGlRenderer::getTextureCreator()
{
    throw std::logic_error("Not implemented");
}
