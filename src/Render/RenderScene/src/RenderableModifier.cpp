#include <RenderScene/RenderableModifier.h>

#include <RenderScene/Renderable.h>

#include <Render2d/GeometryBatch.h>
#include <Render2d/GeometryBatchModifier.h>
#include <Render2d/VertexInfo.h>

//======================================================================================================================
using namespace render_scene;

//======================================================================================================================
RenderableModifier::RenderableModifier(const Renderable& renderable, render_2d::GeometryBatch& batch2d)
    : _renderable(renderable)
    , _batch2d(batch2d)
{
}

//======================================================================================================================
void RenderableModifier::move(const ScreenOffsetVec& offset)
{
    using Batch2dMod = render_2d::GeometryBatchModifier;

    const auto moveVertex = [&offset](Batch2dMod::VertexIdx, render_2d::VertexInfo& vertexInfo) {
        vertexInfo.coords.x += offset.x;
        vertexInfo.coords.y += offset.y;
    };

    // TODO: reuse when new operations supported
    const auto& renderableChunk2d = _renderable.getRenderable2d().getGeometry();
    _batch2d.modify([&renderableChunk2d, &moveVertex](render_2d::GeometryBatchModifier& batchMod) {
        for (const auto& primId : renderableChunk2d.triangles)
            batchMod.forEachPrimitiveVertex(primId, moveVertex);

        for (const auto& primId : renderableChunk2d.lines)
            batchMod.forEachPrimitiveVertex(primId, moveVertex);

        for (const auto& primId : renderableChunk2d.points)
            batchMod.forEachPrimitiveVertex(primId, moveVertex);
    });
}
