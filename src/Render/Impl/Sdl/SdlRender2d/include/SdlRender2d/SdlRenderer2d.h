#pragma once

#include <Render2d/Renderer.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace sdl_render_2d::details {
    class PrimitiveVariant;
}

//======================================================================================================================
namespace sdl_winsys {
    class SdlWindow;
}

//======================================================================================================================
namespace texture_storage {
    class TextureStorage;
}

//======================================================================================================================
struct SDL_Renderer;

//======================================================================================================================
namespace sdl_render_2d {
    //==================================================================================================================
    class SdlRenderer2d final : public render_2d::Renderer {
    public:
        SdlRenderer2d(sdl_winsys::SdlWindow&, const texture_storage::TextureStorage&);
        ~SdlRenderer2d();

        void clear(const content::Color&) override;
        void finalizeRender() override;

        void setBaseRenderResolution(uint16 width, uint16 height) override;

        //--------------------------------------------------------------------------------------------------------------
        uptr<render_2d::GeometryBatch> createGeometryBatch() override;
        void renderGeometryBatch(const render_2d::GeometryBatch&) override;

        //--------------------------------------------------------------------------------------------------------------
        SDL_Renderer& getSdlRenderer();
        const SDL_Renderer& getSdlRenderer() const;

    private:
        void _renderAsPoint2d(const details::PrimitiveVariant&);
        void _renderAsLine(const details::PrimitiveVariant&);
        void _renderAsTriangle(const details::PrimitiveVariant&);

        //--------------------------------------------------------------------------------------------------------------
        // Origin: top-left corner
        // Ox: to the right
        // Oy: downwards
        // Unit: pixel
        struct SdlScreenPoint2d final {
            float x;
            float y;
        };

        SdlScreenPoint2d _toSdlScreenPoint2d(const geometry_2d::Point2d&) const;

    private:
        const texture_storage::TextureStorage& _textureStorage;

        struct Pimpl;
        uptr<Pimpl> _pimpl;
    };
}
