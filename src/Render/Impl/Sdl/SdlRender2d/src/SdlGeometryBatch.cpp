#include "SdlGeometryBatch.h"

#include "Details/PrimitiveVariant.h"

#include <Geometry2d/Line.h>
#include <Geometry2d/Point2d.h>
#include <Geometry2d/Triangle.h>

//======================================================================================================================
using render_2d::RenderableGeometry;
using sdl_render_2d::SdlGeometryBatch;
using sdl_render_2d::details::PrimitiveVariant;

//======================================================================================================================
void SdlGeometryBatch::clear()
{
    _primitives.clear();
}

//======================================================================================================================
void SdlGeometryBatch::add(const RenderableGeometry<geometry_2d::Point2d>& point)
{
    _primitives.push_back({
        .primitiveCoordArray = {point.primitive.x, point.primitive.y},
        .mainColor = point.contentTraits.color,
        .type = PrimitiveVariant::PrimitiveType::Point,
    });
}

//======================================================================================================================
void SdlGeometryBatch::add(const RenderableGeometry<geometry_2d::Line>& line)
{
    const auto& startPt = line.primitive.startPt;
    const auto& finalPt = line.primitive.finalPt;

    _primitives.push_back({
        .primitiveCoordArray = {startPt.x, startPt.y, finalPt.x, finalPt.y},
        .mainColor = line.contentTraits.lineColor,
        .type = PrimitiveVariant::PrimitiveType::Line,
    });
}

//======================================================================================================================
void SdlGeometryBatch::add(const RenderableGeometry<geometry_2d::Triangle>& triangle)
{
    const auto& pt1 = triangle.primitive.pt1;
    const auto& pt2 = triangle.primitive.pt2;
    const auto& pt3 = triangle.primitive.pt3;
    const auto& color = std::get<content::Color>(triangle.contentTraits.faceContent);

    _primitives.push_back({
        .primitiveCoordArray = {pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y},
        .mainColor = color,
        .type = PrimitiveVariant::PrimitiveType::Triangle,
    });
}

//======================================================================================================================
auto SdlGeometryBatch::_getPrimitives() const -> const Vector<PrimitiveVariant>&
{
    return _primitives;
}
