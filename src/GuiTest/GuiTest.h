#pragma once

#include <Framework/Application.h>
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
    ShouldQuit _processEvent(const app_event::AppEvent&);
    void _render();

private:
    uptr<winsys::Window> _appWindow;
    uptr<render::Renderer> _renderer;
};
