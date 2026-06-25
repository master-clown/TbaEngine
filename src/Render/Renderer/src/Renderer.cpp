#include <Renderer/Renderer.h>

#include <TextureStorage/TextureStorage.h>

#include <cassert>

//======================================================================================================================
using render::Renderer;

//======================================================================================================================
Renderer::Renderer(renderer_context::RendererContextRaii rendererContext)
    : _rendererContext(std::move(rendererContext))
    , _textureStorage(makeUPtr<texture_storage::TextureStorage>())
{
}

//======================================================================================================================
Renderer::~Renderer() = default;

//======================================================================================================================
renderer_context::RendererContext& Renderer::getRendererContext()
{
    return const_cast<renderer_context::RendererContext&>(static_cast<const Renderer&>(*this).getRendererContext());
}

//======================================================================================================================
const renderer_context::RendererContext& Renderer::getRendererContext() const
{
    return *_rendererContext;
}

//======================================================================================================================
texture_storage::TextureStorage& Renderer::getTextureStorage()
{
    return const_cast<texture_storage::TextureStorage&>(static_cast<const Renderer&>(*this).getTextureStorage());
}

//======================================================================================================================
const texture_storage::TextureStorage& Renderer::getTextureStorage() const
{
    assert(_textureStorage);
    return *_textureStorage;
}
