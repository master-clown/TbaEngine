#pragma once

#include <Content/Color.h>
#include <GuiAppTemplate/GuiAppWithRenderer.hpp>
#include <Render2d/GeometryBatch.h>
#include <Render2d/GeometryBatchModifier.h>
#include <Render2d/Renderer.h>
#include <Renderer/Renderer.h>
#include <SdlFramework/SdlFramework.h>
#include <Texture/TextureSampler.h>
#include <Texture/TextureSamplingParameters.h>
#include <Texture/TexturingMgr.h>
#include <Texture/TexturingObjectsCreator.h>
#include <Winsys/WindowOptions.h>

#include <functional>

//======================================================================================================================
using InitSceneGeometryBatch = std::function<void(render::Renderer&, render_2d::GeometryBatchModifier&)>;
using UseTexturing = bool;

//======================================================================================================================
template <class RendererPreconfigOptions>
class GeometryBatchRenderingApp final : public gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions> {
    using Super = gui_app_template::GuiAppWithRenderer<RendererPreconfigOptions>;

public:
    GeometryBatchRenderingApp(const String& wndTitle,
                              InitSceneGeometryBatch initSceneGeometryBatch,
                              UseTexturing useTexturing)
        : Super(winsys::WindowOptions{
              .wndTitle = wndTitle,
          })
        , _initSceneGeometryBatch(std::move(initSceneGeometryBatch))
        , _useTexturing(useTexturing)
    {
    }

private:
    void _initAppWithRenderer() override
    {
        auto& renderer = this->getRenderer();

        if (_useTexturing) {
            _defaultTextureSampler = renderer.getTexturingMgr().getTexturingObjectsCreator().createSampler({});
            renderer.getTexturingMgr().setCurrentTextureSampler(*_defaultTextureSampler);
        }

        auto& renderer2d = renderer.get2dRenderer();
        _sceneGeometryBatch = renderer2d.createGeometryBatch();

        _sceneGeometryBatch->modify([this](render_2d::GeometryBatchModifier& modifier) {
            _initSceneGeometryBatch(this->getRenderer(), modifier);
        });
    }

    void _render() override
    {
        this->getRenderer().clear(content::Color::black);

        auto& renderer2d = this->getRenderer().get2dRenderer();
        renderer2d.renderGeometryBatch(*_sceneGeometryBatch);

        this->getRenderer().finalizeRender();
    }

    uptr<framework::Framework> _createFramework() override
    {
        return makeUPtr<sdl_framework::SdlFramework>();
    }

private:
    uptr<texture::TextureSampler> _defaultTextureSampler;
    uptr<render_2d::GeometryBatch> _sceneGeometryBatch;
    InitSceneGeometryBatch _initSceneGeometryBatch;
    UseTexturing _useTexturing;
};
