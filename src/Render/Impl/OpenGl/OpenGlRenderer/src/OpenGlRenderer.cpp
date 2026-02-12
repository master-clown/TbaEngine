#include <OpenGlRenderer/OpenGlRenderer.h>

#include "OpenGlLibraryRaii.h"

#include <cassert>

//==================================================================================================================
opengl_render::OpenGlRenderer::OpenGlRenderer(winsys::Window& window)
    : _openGlLibraryRaii(makeUPtr<opengl_render::OpenGlLibraryRaii>())
{
}

//==================================================================================================================
opengl_render::OpenGlRenderer::~OpenGlRenderer() = default;

//==================================================================================================================
void opengl_render::OpenGlRenderer::clear(const content::Color& color)
{
    // get2dRenderer().clear(color);
}

//==================================================================================================================
void opengl_render::OpenGlRenderer::finalizeRender()
{
    // get2dRenderer().finalizeRender();
}

//==================================================================================================================
render_2d::Renderer& opengl_render::OpenGlRenderer::get2dRenderer()
{
    throw std::logic_error("Not implemented");
}

//==================================================================================================================
render_3d::Renderer& opengl_render::OpenGlRenderer::get3dRenderer()
{
    throw std::logic_error("Not implemented");
}
