#pragma once

#include <Common/Stl/Vector.h>
#include <Render2d/PrimitiveId.h>

//======================================================================================================================
namespace render_scene {
    struct GeometryChunk2d final {
        Vector<render_2d::PrimitiveId> points;
        Vector<render_2d::PrimitiveId> lines;
        Vector<render_2d::PrimitiveId> triangles;
    };
}
