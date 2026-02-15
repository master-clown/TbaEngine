#include <RendererContext/RendererContextRaii.h>

#include <RendererContext/RendererContext.h>

#include <Logger/BasicLogging.h>

#include <cassert>

//======================================================================================================================
using namespace renderer_context;

//======================================================================================================================
RendererContextRaii::RendererContextRaii(uptr<RendererContext> context, TargetWindow& window)
    : _context(std::move(context))
{
    if (_context)
        _context->initContext(window);
}

//======================================================================================================================
RendererContextRaii::~RendererContextRaii()
{
    if (!_context)
        return;

    try {
        _context->freeContext();
    }
    catch (const std::exception& ex) {
        LOG_ERROR("Failed to free context: {}", ex.what());
    }
}

//======================================================================================================================
RendererContextRaii::RendererContextRaii(RendererContextRaii&&) = default;

//======================================================================================================================
RendererContextRaii& RendererContextRaii::operator=(RendererContextRaii&&) = default;

//======================================================================================================================
RendererContext& RendererContextRaii::operator*()
{
    return const_cast<RendererContext&>(static_cast<const RendererContextRaii&>(*this).operator*());
}

//======================================================================================================================
const RendererContext& RendererContextRaii::operator*() const
{
    if (!_context)
        throw std::runtime_error("Trying to use an empty RenderContext!");

    return *_context;
}

//======================================================================================================================
RendererContext* RendererContextRaii::operator->()
{
    return const_cast<RendererContext*>(static_cast<const RendererContextRaii&>(*this).operator->());
}

//======================================================================================================================
const RendererContext* RendererContextRaii::operator->() const
{
    if (!_context)
        throw std::runtime_error("Trying to use an empty RenderContext!");

    return _context.get();
}
