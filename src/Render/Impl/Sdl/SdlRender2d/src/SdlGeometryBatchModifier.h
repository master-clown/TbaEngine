#pragma once

#include <Render2d/GeometryBatchModifier.h>

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatch;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatchModifier final : public render_2d::GeometryBatchModifier {
    public:
        explicit SdlGeometryBatchModifier(SdlGeometryBatch&);

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;

        //--------------------------------------------------------------------------------------------------------------
        void append(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        void append(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        SdlGeometryBatch& _batch;
    };
}
