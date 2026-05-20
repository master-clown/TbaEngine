#include <RenderScene/TracedGeometryBatchModifier2d.h>

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>

//======================================================================================================================
using render_scene::TracedGeometryBatchModifier2d;

using render_2d::PrimitiveId;
using render_scene::GeometryChunk2d;

//======================================================================================================================
TracedGeometryBatchModifier2d::TracedGeometryBatchModifier2d(WrappedBatchModifier& wrappedModifier)
    : _wrappedBatchModifier(wrappedModifier)
{
}

//======================================================================================================================
GeometryChunk2d&& TracedGeometryBatchModifier2d::getAccumulatedGeometry()
{
    return std::move(_accumulatedGeometry);
}

//======================================================================================================================
void TracedGeometryBatchModifier2d::clear()
{
    _accumulatedGeometry = GeometryChunk2d{};

    _wrappedBatchModifier.clear();
}

//======================================================================================================================
PrimitiveId TracedGeometryBatchModifier2d::append(const render_2d::RenderableGeometry<geometry_2d::Point2d>& prim)
{
    const auto primId = _wrappedBatchModifier.append(prim);
    _accumulatedGeometry.points.push_back(primId);

    return primId;
}

//======================================================================================================================
PrimitiveId TracedGeometryBatchModifier2d::append(const render_2d::RenderableGeometry<geometry_2d::Line>& prim)
{
    const auto primId = _wrappedBatchModifier.append(prim);
    _accumulatedGeometry.lines.push_back(primId);

    return primId;
}

//======================================================================================================================
PrimitiveId TracedGeometryBatchModifier2d::append(const render_2d::RenderableGeometry<geometry_2d::Triangle>& prim)
{
    const auto primId = _wrappedBatchModifier.append(prim);
    _accumulatedGeometry.triangles.push_back(primId);

    return primId;
}
