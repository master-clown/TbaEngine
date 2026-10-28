#pragma once

#include <Common/Memory.h>
#include <Common/Stl/HashMap.h>
#include <Common/Stl/Vector.h>
#include <Render2d/GeometryBatch.h>
#include <Render2d/PrimitiveId.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    struct PrimitiveVariant;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatchModifier;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
namespace sdl_render_2d {
    class SdlGeometryBatch final : public render_2d::GeometryBatch {
    public:
        explicit SdlGeometryBatch(const texture_storage::TextureStorage&);
        ~SdlGeometryBatch();

        //--------------------------------------------------------------------------------------------------------------
        void modify(const std::function<void(render_2d::GeometryBatchModifier&)>&) override;

    private:
        friend class SdlRenderer2d;
        const Vector<details::PrimitiveVariant>& _getPrimitives() const;

        //--------------------------------------------------------------------------------------------------------------
        friend class SdlGeometryBatchModifier;
        Vector<details::PrimitiveVariant>& _getPrimitives();

        using _PrimitiveIdx = uint32;
        using PrimIdToIdxMap = HashMap<render_2d::PrimitiveId, _PrimitiveIdx>;
        PrimIdToIdxMap& _getPrimIdToIdxMap();

    private:
        uptr<render_2d::GeometryBatchModifier> _modifier;
        Vector<details::PrimitiveVariant> _primitives;
        PrimIdToIdxMap _primIdToIdxMap;
    };
}
