#include "OpenGlContextCreator.h"

#include "OpenGlContextOnSdl.h"

#include <OpenGlContext/OpenGlPreconfigOptions.h>
#include <RendererContext/RendererContextRaii.h>

#include <cassert>

//======================================================================================================================
using renderer_context::RendererContextRaii;
using renderer_context::RendererPreconfigOptions;
using sdl_winsys::OpenGlContextCreator;

//======================================================================================================================
OpenGlContextCreator::OpenGlContextCreator(uptr<RendererPreconfigOptions> preconfigOptions)
    : renderer_context::RendererContextCreator(std::move(preconfigOptions))
    , _contextToCreate(makeUPtr<OpenGlContextOnSdl>())
{
}

//======================================================================================================================
OpenGlContextCreator::~OpenGlContextCreator() = default;

//======================================================================================================================
void OpenGlContextCreator::configureBeforeWindowCreation()
{
    assert(dynamic_cast<const opengl_context::OpenGlPreconfigOptions*>(&getRendererPreconfigOptions()));

    assert(_contextToCreate);
    assert(dynamic_cast<OpenGlContextOnSdl*>(_contextToCreate.get()));
    auto& context = static_cast<OpenGlContextOnSdl&>(*_contextToCreate);

    // TODO: allow customization
    context.setGlProfile(opengl_context::OpenGlContext::GlProfile::Core);
    context.setGlMajorVersion(4);
    context.setGlMinorVersion(6);
}

//======================================================================================================================
RendererContextRaii OpenGlContextCreator::createRendererContext(TargetWindow& targetWindow)
{
    assert(_contextToCreate);
    return RendererContextRaii(std::move(_contextToCreate), targetWindow);
}
