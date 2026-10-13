#pragma once

#include <Render2d/PrimitiveId.h>
#include <Render2d/RenderableGeometry.h>

#include <functional>

//======================================================================================================================
namespace render_2d {
    struct VertexInfo;
}

//======================================================================================================================
namespace geometry_2d {
    struct Point2d;
    struct Line;
    struct Triangle;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatchModifier {
    public:
        virtual ~GeometryBatchModifier();

        //--------------------------------------------------------------------------------------------------------------
        virtual void clear() = 0;

        //--------------------------------------------------------------------------------------------------------------
        // TODO: add bulk operations (to allocate the memory only once)
        virtual PrimitiveId append(const RenderableGeometry<geometry_2d::Point2d>&) = 0;
        virtual PrimitiveId append(const RenderableGeometry<geometry_2d::Line>&) = 0;
        virtual PrimitiveId append(const RenderableGeometry<geometry_2d::Triangle>&) = 0;

        //--------------------------------------------------------------------------------------------------------------
        // TODO: improve efficiency (e.g. iterator?). Functor is overkill here (is it?)
        using PrimitiveVertexAction = std::function<void(uint8 iVertex, VertexInfo&)>;
        virtual void forEachPrimitiveVertex(PrimitiveId, const PrimitiveVertexAction&) = 0;
    };
}
