#include <Renderer/Renderer.h>

//======================================================================================================================
using render::Renderer;

//======================================================================================================================
Renderer::Renderer(renderer_context::RendererContextRaii rendererContext)
    : _rendererContext(std::move(rendererContext))
{
}

//======================================================================================================================
Renderer::~Renderer() = default;

//======================================================================================================================
const renderer_context::RendererContext& Renderer::getRendererContext() const
{
    return *_rendererContext;
}
