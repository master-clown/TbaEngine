#include <RendererContext/RendererContextCreator.h>

#include <RendererContext/RendererPreconfigOptions.h>

#include <cassert>

//======================================================================================================================
using namespace renderer_context;

//======================================================================================================================
RendererContextCreator::RendererContextCreator(uptr<RendererPreconfigOptions> preconfigOptions)
    : _rendererPreconfigOptions(std::move(preconfigOptions))
{
    assert(_rendererPreconfigOptions);
}

//======================================================================================================================
RendererContextCreator::~RendererContextCreator() = default;

//======================================================================================================================
RendererType RendererContextCreator::getRendererType() const
{
    return _rendererPreconfigOptions->getRendererType();
}

//======================================================================================================================
const RendererPreconfigOptions& RendererContextCreator::getRendererPreconfigOptions() const
{
    return *_rendererPreconfigOptions;
}
