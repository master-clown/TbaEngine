#include <TextureStorage/TextureStorage.h>

#include <Texture/Texture.h>

#include <cassert>

//======================================================================================================================
using texture_storage::TextureId;
using texture_storage::TextureStorage;

using texture::Texture;

//======================================================================================================================
void TextureStorage::clear()
{
    _textures.clear();
}

//======================================================================================================================
TextureId TextureStorage::add(uptr<Texture> tex)
{
    assert(tex);

    const auto id = _nextId.fetch_add(1);
    [[maybe_unused]] const auto [it, hasEmplaced] = _textures.emplace(id, std::move(tex));
    assert(hasEmplaced);

    return TextureId{.id = id};
}

//======================================================================================================================
Texture& TextureStorage::get(const TextureId id)
{
    return const_cast<Texture&>(static_cast<const TextureStorage&>(*this).get(id));
}

//======================================================================================================================
const Texture& TextureStorage::get(const TextureId id) const
{
    const auto it = _textures.find(id);
    assert(it != _textures.cend());

    return *it->second;
}

//======================================================================================================================
TextureStorage& TextureStorage::getInstance()
{
    static TextureStorage instance;
    return instance;
}
