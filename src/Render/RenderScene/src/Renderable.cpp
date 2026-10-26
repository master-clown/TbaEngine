#include <RenderScene/Renderable.h>

//======================================================================================================================
using render_scene::Renderable;
using render_scene::Renderable2d;

//======================================================================================================================
Renderable::Renderable(Renderable2d renderable2d)
    : _2dPart(std::move(renderable2d))
{
}

//======================================================================================================================
Renderable::Renderable() = default;

//======================================================================================================================
const Renderable2d& Renderable::getRenderable2d() const noexcept
{
    return _2dPart;
}
