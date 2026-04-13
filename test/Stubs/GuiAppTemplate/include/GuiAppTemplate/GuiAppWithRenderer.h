#pragma once

#include <GuiAppTemplate/GuiAppTemplate.h>

//======================================================================================================================
namespace render {
    class Renderer;
}

//======================================================================================================================
namespace gui_app_template {
    template <class RendererPreconfigOptions>
    class GuiAppWithRenderer : public GuiAppTemplate {
        using Super = GuiAppTemplate;

    public:
        explicit GuiAppWithRenderer(winsys::WindowOptions);

        //--------------------------------------------------------------------------------------------------------------
        render::Renderer& getRenderer();

    protected:
        virtual void _initAppWithRenderer() = 0;

        //--------------------------------------------------------------------------------------------------------------
        void _init() override;
        uptr<winsys::Window> _createWindow(const winsys::WindowOptions& windowOptions) override final;

    private:
        uptr<render::Renderer> _renderer;
    };
}
