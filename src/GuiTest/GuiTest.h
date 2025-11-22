#pragma once

#include <Framework/Application.h>
#include <Geometry2d/ScreenCoordinate.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace render {
    class Renderer;
}

//======================================================================================================================
class GuiTest final : public framework::Application {
public:
    GuiTest();
    ~GuiTest();

private:
    uptr<framework::Framework> _init() override;
    ShouldQuit _iterate(const app_event::AppEvent&) override;

private:
    void _initWindow(framework::Framework&);
    void _initRenderer(framework::Framework&);
    ShouldQuit _processEvent(const app_event::AppEvent&);
    void _render();

private:
    struct GraphicsOptions final {
        geometry_2d::ScreenCoordinate _renderTargetLogicalWidth = 640;
        geometry_2d::ScreenCoordinate _renderTargetLogicalHeigth = 480;
    };

    uptr<winsys::Window> _appWindow;
    uptr<render::Renderer> _renderer;
    GraphicsOptions _graphicsOptions;
};
