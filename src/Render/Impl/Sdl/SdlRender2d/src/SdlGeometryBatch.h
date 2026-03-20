#pragma once

#include <Render2d/GeometryBatch.h>

#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    struct PrimitiveVariant;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatch final : public render_2d::GeometryBatch {
    public:
        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        void add(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void add(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void add(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        friend class SdlRenderer2d;
        const Vector<details::PrimitiveVariant>& _getPrimitives() const;

    private:
        Vector<details::PrimitiveVariant> _primitives;
    };
}
