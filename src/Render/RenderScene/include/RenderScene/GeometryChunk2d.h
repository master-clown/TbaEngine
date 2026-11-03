#pragma once

#include <Common/Stl/Vector.h>
#include <Render2d/PrimitiveId.h>

//======================================================================================================================
namespace render_scene {
    struct GeometryChunk2d final {
        using PrimitiveIds = Vector<render_2d::PrimitiveId>;

        PrimitiveIds points;
        PrimitiveIds lines;
        PrimitiveIds triangles;
    };
}
