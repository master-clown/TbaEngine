#include <RenderScene/RenderableBlueprint.h>

#include <RenderScene/Renderable.h>
#include <RenderScene/Renderable2d.h>
#include <RenderScene/TracedGeometryBatchModifier2d.h>

//======================================================================================================================
using render_scene::RenderableBlueprint;

//======================================================================================================================
RenderableBlueprint::~RenderableBlueprint() = default;

//======================================================================================================================
render_scene::Renderable RenderableBlueprint::makeRenderable(render_scene::TracedGeometryBatchModifier2d& batchMod)
{
    _constructRenderableOnBatch(batchMod);

    return Renderable{Renderable2d{batchMod.build()}};
}
