#include <Texture/TextureSamplingParameters.h>

#include <utility>

//======================================================================================================================
String texture::str(const TextureSamplingParameters::AddressMode mode)
{
    using En = texture::TextureSamplingParameters::AddressMode;

    switch (mode) {
    case En::Repeat: return "AddressMode::Repeat";
    case En::MirroredRepeat: return "AddressMode::MirroredRepeat";
    case En::Clamp: return "AddressMode::Clamp";
    }

    std::unreachable();
}

//======================================================================================================================
String texture::str(const TextureSamplingParameters::Filtering filtering)
{
    using En = texture::TextureSamplingParameters::Filtering;

    switch (filtering) {
    case En::Nearest: return "Filtering::Nearest";
    case En::Linear: return "Filtering::Linear";
    }

    std::unreachable();
}
