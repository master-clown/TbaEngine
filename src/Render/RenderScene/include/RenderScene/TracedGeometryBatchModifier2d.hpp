#pragma once

#include <RenderScene/TracedGeometryBatchModifier2d.h>

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>
#include <Render2d/GeometryBatchModifier.h>

#include <type_traits>

//======================================================================================================================
template <typename Geometry>
void render_scene::TracedGeometryBatchModifier2d::add(const render_2d::RenderableGeometry<Geometry>& primitive)
{
    const auto primId = _wrappedBatchModifier.append(primitive);
    _selectPrimitiveIdsByGeometryType<Geometry>().push_back(primId);
}

//======================================================================================================================
template <typename Geometry>
GeometryChunk2d::PrimitiveIds& render_scene::TracedGeometryBatchModifier2d::_selectPrimitiveIdsByGeometryType()
{
    if constexpr (std::is_same_v<Geometry, geometry_2d::Point2d>)
        return _geometryChunk.points;

    if constexpr (std::is_same_v<Geometry, geometry_2d::Line>)
        return _geometryChunk.lines;

    if constexpr (std::is_same_v<Geometry, geometry_2d::Triangle>)
        return _geometryChunk.triangles;
}
