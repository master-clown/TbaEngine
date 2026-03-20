#pragma once

#include <Render2d/RenderableGeometry.h>

#include <Common/Integers.h>
#include <Common/Memory.h>

//======================================================================================================================
namespace content {
    struct Color;
}

//======================================================================================================================
namespace geometry_2d {
    struct Point2d;
    struct Line;
    struct Triangle;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatch;
}

//======================================================================================================================
namespace render_2d {
    //==================================================================================================================
    class Renderer {
    public:
        virtual ~Renderer();

        // TODO: to separate interface? For both 2D and 3D
        virtual void clear(const content::Color&) = 0;
        virtual void finalizeRender() = 0;
        // end of TODO

        // Set device-independent render viewport.
        // The client of `Renderer` assumes it is the viewport for his geometry,
        // while `Renderer` must properly scale this viewport to the actual render target size.
        virtual void setBaseRenderResolution(uint16 width, uint16 height) = 0;

        //--------------------------------------------------------------------------------------------------------------
        // TODO: remove
        virtual void render(const RenderableGeometry<geometry_2d::Point2d>&) = 0;
        virtual void render(const RenderableGeometry<geometry_2d::Line>&) = 0;
        virtual void render(const RenderableGeometry<geometry_2d::Triangle>&) = 0;

        //--------------------------------------------------------------------------------------------------------------
        // TODO: make pure
        virtual uptr<GeometryBatch> createGeometryBatch()
        {
            return nullptr;
        }

        virtual void renderGeometryBatch(const GeometryBatch&)
        {
        }
    };
}
