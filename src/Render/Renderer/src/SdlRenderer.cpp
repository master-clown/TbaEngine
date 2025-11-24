#include <Renderer/SdlRenderer.h>

#include <Render2d/SdlRenderer.h>

#include <cassert>

//==================================================================================================================
render::SdlRenderer::SdlRenderer()
    : _renderer2d(makeUPtr<render_2d::Renderer>())
{
}

//==================================================================================================================
render::SdlRenderer::~SdlRenderer() = default;

//==================================================================================================================
render_2d::Renderer& render::SdlRenderer::get2dRenderer()
{
    assert(_renderer2d);
    return *_renderer2d;
}

//==================================================================================================================
render_3d::Renderer& render::SdlRenderer::get3dRenderer()
{
    throw std::logic_error("Not implemented");
}
