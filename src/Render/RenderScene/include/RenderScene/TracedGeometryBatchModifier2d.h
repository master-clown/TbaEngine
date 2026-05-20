#pragma once

#include <RenderScene/GeometryChunk2d.h>

#include <Render2d/GeometryBatchModifier.h>

//======================================================================================================================
namespace render_scene {
    class TracedGeometryBatchModifier2d final : public render_2d::GeometryBatchModifier {
    public:
        using WrappedBatchModifier = render_2d::GeometryBatchModifier;
        explicit TracedGeometryBatchModifier2d(WrappedBatchModifier&);

        GeometryChunk2d&& getAccumulatedGeometry();

        //--------------------------------------------------------------------------------------------------------------
        void clear() override;
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Point2d>&) override;
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Line>&) override;
        render_2d::PrimitiveId append(const render_2d::RenderableGeometry<geometry_2d::Triangle>&) override;

    private:
        WrappedBatchModifier& _wrappedBatchModifier;
        GeometryChunk2d _accumulatedGeometry;
    };
}

