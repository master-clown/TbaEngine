#pragma once

#include <Framework/RenderableApplication.h>
#include <Geometry2d/ScreenCoordinate.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace render {
    class Renderer;
}

//======================================================================================================================
class GuiTest final : public framework::RenderableApplication {
public:
    GuiTest();
    ~GuiTest();

private:
    uptr<framework::Framework> _init() override;
    ShouldQuit _iterate(const app_event::AppEvent&) override;
    void _render() override;

private:
    void _initWindow(framework::Framework&);
    void _initRenderer(framework::Framework&);
    ShouldQuit _processEvent(const app_event::AppEvent&);

private:
    struct GraphicsOptions final {
        geometry_2d::ScreenCoordinate _renderTargetLogicalWidth = 640;
        geometry_2d::ScreenCoordinate _renderTargetLogicalHeigth = 480;
    };

    uptr<winsys::Window> _appWindow;
    uptr<render::Renderer> _renderer;
    GraphicsOptions _graphicsOptions;
};
