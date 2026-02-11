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
renderer_context::RendererContext& Renderer::getRendererContext()
{
    return const_cast<renderer_context::RendererContext&>(static_cast<const Renderer&>(*this).getRendererContext());
}

//======================================================================================================================
const renderer_context::RendererContext& Renderer::getRendererContext() const
{
    return *_rendererContext;
}
