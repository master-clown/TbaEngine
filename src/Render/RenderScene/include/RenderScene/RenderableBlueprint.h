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

        // TODO: make sure we extract accumulated geometry from the modifier
        virtual uptr<Renderable> makeRenderable(TracedGeometryBatchModifier2d&) = 0;
    };
}
