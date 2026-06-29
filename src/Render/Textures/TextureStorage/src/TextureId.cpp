#include <TextureStorage/TextureId.h>

//======================================================================================================================
texture_storage::TextureId::operator const Id&() const
{
    return id;
}
