#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace render_scene {
    class Renderable;
    class TracedGeometryBatchModifier2d;
}

//======================================================================================================================
namespace render_scene {
    class RenderableBlueprint {
    public:
        virtual ~RenderableBlueprint();

        Renderable makeRenderable(TracedGeometryBatchModifier2d&);

    private:
        virtual void _constructRenderableOnBatch(TracedGeometryBatchModifier2d&) = 0;
    };
}
