#include <RenderScene/TracedGeometryBatchModifier2d.h>

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/GeometryBatchModifier.h>

//======================================================================================================================
using render_scene::TracedGeometryBatchModifier2d;

using geometry_2d::Line;
using geometry_2d::Point2d;
using geometry_2d::Triangle;

using render_2d::PrimitiveId;
using render_scene::GeometryChunk2d;

//======================================================================================================================
TracedGeometryBatchModifier2d::TracedGeometryBatchModifier2d(WrappedBatchModifier& wrappedModifier)
    : _wrappedBatchModifier(wrappedModifier)
{
}

//======================================================================================================================
GeometryChunk2d&& TracedGeometryBatchModifier2d::build()
{
    return std::move(_geometryChunk);
}

//======================================================================================================================
template <>
void TracedGeometryBatchModifier2d::add<Point2d>(const render_2d::RenderableGeometry<Point2d>& primitive)
{
    _geometryChunk.points.push_back(_wrappedBatchModifier.append(primitive));
}

//======================================================================================================================
template <>
void TracedGeometryBatchModifier2d::add<Line>(const render_2d::RenderableGeometry<Line>& primitive)
{
    _geometryChunk.lines.push_back(_wrappedBatchModifier.append(primitive));
}

//======================================================================================================================
template <>
void TracedGeometryBatchModifier2d::add<Triangle>(const render_2d::RenderableGeometry<Triangle>& primitive)
{
    _geometryChunk.triangles.push_back(_wrappedBatchModifier.append(primitive));
}
