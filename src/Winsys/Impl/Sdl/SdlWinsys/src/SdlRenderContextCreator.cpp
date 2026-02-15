#include "SdlRenderContextCreator.h"

#include <RendererContext/RendererContextRaii.h>
#include <SdlRenderContext/SdlRenderContext.h>
#include <SdlRenderContext/SdlRenderPreconfigOptions.h>

#include <cassert>

//======================================================================================================================
using renderer_context::RendererContextRaii;
using sdl_winsys::SdlRenderContextCreator;

//======================================================================================================================
SdlRenderContextCreator::SdlRenderContextCreator(uptr<renderer_context::RendererPreconfigOptions> preconfigOptions)
    : renderer_context::RendererContextCreator(std::move(preconfigOptions))
{
}

//======================================================================================================================
SdlRenderContextCreator::~SdlRenderContextCreator() = default;

//======================================================================================================================
void SdlRenderContextCreator::configureBeforeWindowCreation()
{
    assert(dynamic_cast<const sdl_render_context::SdlRenderPreconfigOptions*>(&getRendererPreconfigOptions()));
}

//======================================================================================================================
RendererContextRaii SdlRenderContextCreator::createRendererContext(TargetWindow& targetWindow)
{
    return RendererContextRaii(makeUPtr<sdl_render_context::SdlRenderContext>(), targetWindow);
}
