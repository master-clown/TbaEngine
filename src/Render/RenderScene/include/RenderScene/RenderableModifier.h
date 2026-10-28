#pragma once

#include <Geometry2d/ScreenCoordinate.h>

//======================================================================================================================
namespace render_scene {
    class Renderable;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatch;
}

//======================================================================================================================
namespace render_scene {
    class RenderableModifier final {
    public:
        RenderableModifier(const Renderable&, render_2d::GeometryBatch&);

        // TODO: use general vectors
        struct ScreenOffsetVec final {
            geometry_2d::ScreenCoordinate x = 0;
            geometry_2d::ScreenCoordinate y = 0;
        };
        void move(const ScreenOffsetVec&);

    private:
        const Renderable& _renderable;
        render_2d::GeometryBatch& _batch2d;
    };
}
