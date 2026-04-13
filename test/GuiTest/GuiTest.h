#pragma once

#include <Framework/RenderableApplication.h>
#include <Geometry2d/ScreenCoordinate.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace render {
    class Renderer;
}

//======================================================================================================================
namespace render_2d {
    class GeometryBatch;
}

//======================================================================================================================
class GuiTest final : public framework::RenderableApplication {
public:
    GuiTest();
    ~GuiTest();

private:
    uptr<framework::Framework> _createFramework() override;
    void _init() override;
    ShouldQuit _iterate(const app_event::AppEvent&) override;
    void _render() override;

private:
    void _initWindow(framework::Framework&);
    void _initRenderer(framework::Framework&);
    ShouldQuit _processEvent(const app_event::AppEvent&);

private:
    struct GraphicsOptions final {
        uint16 _renderTargetLogicalWidth = 640;
        uint16 _renderTargetLogicalHeigth = 480;
    };

    uptr<winsys::Window> _appWindow;
    uptr<render::Renderer> _renderer;
    GraphicsOptions _graphicsOptions;
    uptr<render_2d::GeometryBatch> _simple2dGeometryBatch;
};
