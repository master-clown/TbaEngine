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
    , _contextToCreate(makeUPtr<sdl_render_context::SdlRenderContext>())
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
    assert(_contextToCreate);
    return RendererContextRaii(std::move(_contextToCreate), targetWindow);
}
