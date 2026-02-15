#include <SdlWinsys/SdlWindowMgr.h>

#include "OpenGlContextCreator.h"
#include "SdlRenderContextCreator.h"

#include <SdlWinsys/SdlWindow.h>

#include <RendererContext/RendererPreconfigOptions.h>

//======================================================================================================================
using namespace sdl_winsys;
using namespace winsys;

//======================================================================================================================
SdlWindowMgr::SdlWindowMgr(event_sys::NativeEventListeners& nativeEventListeners)
    : WindowMgr(nativeEventListeners)
{
}

//======================================================================================================================
SdlWindowMgr::~SdlWindowMgr() = default;

//======================================================================================================================
uptr<Window> SdlWindowMgr::createWindow(CreateWindowOptions createWindowOptions)
{
    auto rendererContextCreator = [&] -> uptr<renderer_context::RendererContextCreator> {
        if (!createWindowOptions.rendererPreconfigOptions.has_value())
            return nullptr;

        auto rendererPreconfigOptions = std::move(*createWindowOptions.rendererPreconfigOptions);
        if (!rendererPreconfigOptions)
            return nullptr;

        using RenderType = renderer_context::RendererType;
        const auto rendererType = rendererPreconfigOptions->getRendererType();

        switch (rendererType) {
        case RenderType::OpenGl: return makeUPtr<OpenGlContextCreator>(std::move(rendererPreconfigOptions));
        case RenderType::Sdl: return makeUPtr<SdlRenderContextCreator>(std::move(rendererPreconfigOptions));
        default: break;
        }

        // TODO: add VERBOSE on not supporting passed renderer type

        return nullptr;
    }();

    return std::make_unique<SdlWindow>(getNativeEventListeners(),
                                       std::move(createWindowOptions.winOptions),
                                       std::move(rendererContextCreator));
}
