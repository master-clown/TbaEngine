#pragma once

#include <Framework/Application.h>
#include <Winsys/Window.h>

//======================================================================================================================
class GuiTest final : public framework::Application {
private:
    uptr<framework::Framework> _init() override;
    ShouldQuit _iterate(const app_event::AppEvent&) override;

private:
    uptr<winsys::Window> _appWindow;
};
