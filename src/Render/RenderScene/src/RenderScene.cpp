#include <RenderScene/RenderScene.h>

#include <RenderScene/Renderable.h>
#include <RenderScene/RenderableBlueprint.h>
#include <RenderScene/TracedGeometryBatchModifier2d.h>

#include <Render2d/GeometryBatch.h>
#include <Render2d/Renderer.h>

#include <cassert>

//======================================================================================================================
using namespace render_scene;

//======================================================================================================================
RenderScene::RenderScene(render_2d::Renderer& renderer2d)
    : _geometryBatch2d(renderer2d.createGeometryBatch())
{
}

//======================================================================================================================
RenderScene::~RenderScene() = default;

//======================================================================================================================
const render_2d::GeometryBatch& RenderScene::getGeometryBatch2d() const
{
    assert(_geometryBatch2d);
    return *_geometryBatch2d;
}

//======================================================================================================================
// TODO: `modify()` for each renderable? Very unoptimal!
Renderable& RenderScene::addRenderable(RenderableBlueprint& renderableBlueprint)
{
    assert(_geometryBatch2d);

    uptr<Renderable> renderable;
    _geometryBatch2d->modify([&renderable, &renderableBlueprint](render_2d::GeometryBatchModifier& modifier) {
        TracedGeometryBatchModifier2d tracedModifier{modifier};
        renderable = renderableBlueprint.makeRenderable(tracedModifier);
    });

    assert(renderable);

    auto& renderableRef = *renderable;
    _renderables.emplace_back(std::move(renderable));

    return renderableRef;
}
