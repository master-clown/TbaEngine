#pragma once

#include <Framework/RenderableApplication.h>
#include <Winsys/Window.h>

//======================================================================================================================
namespace gui_app_template {
    class GuiAppTemplate : public framework::RenderableApplication {
    public:
        explicit GuiAppTemplate(winsys::WindowOptions);
        ~GuiAppTemplate();

    protected:
        virtual uptr<winsys::Window> _createWindow(const winsys::WindowOptions&);
        virtual ShouldQuit _processEvent(const app_event::AppEvent&);

        //--------------------------------------------------------------------------------------------------------------
        winsys::Window& _getWindow();
        const winsys::Window& _getWindow() const;

    private:
        void _init() override;
        ShouldQuit _iterate(const app_event::AppEvent&) override;
        void _render() override;

    private:
        winsys::WindowOptions _appWindowOptions;
        uptr<winsys::Window> _appWindow;
    };
}
