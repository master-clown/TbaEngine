#pragma once

#include <RenderScene/GeometryChunk2d.h>

//======================================================================================================================
namespace render_scene {
    class Renderable2d final {
    public:
        explicit Renderable2d(GeometryChunk2d);
        Renderable2d();

        const GeometryChunk2d& getGeometry() const;

    private:
        GeometryChunk2d _geometry;
    };
}
