#include <Content/Color.h>

//======================================================================================================================
namespace content {
    constexpr Color Color::transparent{.a = 0};
    constexpr Color Color::black{.r = 0, .g = 0, .b = 0, .a = 255};
    constexpr Color Color::white{.r = 255, .g = 255, .b = 255, .a = 255};
}
