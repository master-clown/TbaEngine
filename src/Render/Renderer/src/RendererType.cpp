#include <Renderer/RendererType.h>

//======================================================================================================================
String str(const render::RendererType type) noexcept
{
    using Type = render::RendererType;

    switch (type) {
    case Type::OpenGl: return "RendererType::OpenGl";
    case Type::Vulkan: return "RendererType::Vulkan";
    case Type::Direct3d: return "RendererType::Direct3d";
    case Type::Sdl: return "RendererType::Sdl";
    default: break;
    }

    return strFormat("<Unknown RendererType({})>", str(static_cast<std::underlying_type_t<Type>>(type)));
}
