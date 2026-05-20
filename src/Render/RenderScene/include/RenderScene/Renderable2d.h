#pragma once

#include <RenderScene/GeometryChunk2d.h>

//======================================================================================================================
namespace render_scene {
    class Renderable2d final {
    public:
        explicit Renderable2d(GeometryChunk2d chunk)
            : _geometry(std::move(chunk))
        {
        }

        const GeometryChunk2d& getGeometry() const
        {
            return _geometry;
        }

    private:
        GeometryChunk2d _geometry;
    };
}
