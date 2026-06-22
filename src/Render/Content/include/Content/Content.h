#pragma once

#include <Content/Color.h>

#include <TextureStorage/TextureId.h>

#include <variant>

//======================================================================================================================
namespace content {
    using Content = std::variant<
        Color,
        texture_storage::TextureId>;
}
