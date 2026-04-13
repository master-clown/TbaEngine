#pragma once

#include <Render2d/GeometryBatch.h>

#include <Common/Memory.h>
#include <Common/Stl/Vector.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    struct PrimitiveVariant;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatchModifier;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatch final : public render_2d::GeometryBatch {
    public:
        SdlGeometryBatch();
        ~SdlGeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        void modify(const std::function<void(render_2d::GeometryBatchModifier&)>&) override;

    private:
        friend class SdlRenderer2d;
        const Vector<details::PrimitiveVariant>& _getPrimitives() const;

        //--------------------------------------------------------------------------------------------------------------
        friend class SdlGeometryBatchModifier;
        Vector<details::PrimitiveVariant>& _getPrimitives();

    private:
        uptr<render_2d::GeometryBatchModifier> _modifier;
        Vector<details::PrimitiveVariant> _primitives;
    };
}
