#pragma once

#include <RenderScene/GeometryChunk2d.h>

#include <Render2d/RenderableGeometry.h>

//======================================================================================================================
namespace render_2d {
    class GeometryBatchModifier;
}

//======================================================================================================================
namespace render_scene {
    // TODO: rename to `GeometryChunk2dBuilder`
    class TracedGeometryBatchModifier2d final {
    public:
        using WrappedBatchModifier = render_2d::GeometryBatchModifier;
        explicit TracedGeometryBatchModifier2d(WrappedBatchModifier&);

        GeometryChunk2d&& build();

        //--------------------------------------------------------------------------------------------------------------
        template <typename Geometry>
        void add(const render_2d::RenderableGeometry<Geometry>&);

    private:
        WrappedBatchModifier& _wrappedBatchModifier;
        GeometryChunk2d _geometryChunk;
    };
}

