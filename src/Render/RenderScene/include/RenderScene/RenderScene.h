#pragma once

#include <RenderScene/Renderable2d.h>

#include <Common/Memory.h>
#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace render_2d {
    class GeometryBatch;
    class Renderer;
}

//======================================================================================================================
namespace render_scene {
    class Renderable;
    class RenderableBlueprint;
}

//======================================================================================================================
namespace render_scene {
    class RenderScene final {
    public:
        explicit RenderScene(render_2d::Renderer&);
        ~RenderScene();

        const render_2d::GeometryBatch& getGeometryBatch2d() const;

        Renderable& addRenderable(RenderableBlueprint&);

    private:
        uptr<render_2d::GeometryBatch> _geometryBatch2d;
        Vector<uptr<Renderable>> _renderables;
    };
}
