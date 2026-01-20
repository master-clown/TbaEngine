#include <Mouse/MouseButton.h>

#include <utility>

//======================================================================================================================
String mouse::str(const mouse::MouseButton mouseBtn)
{
    using En = mouse::MouseButton;

    switch (mouseBtn) {
    case En::None: return "None";
    case En::Left: return "Left";
    case En::Right: return "Right";
    case En::Middle: return "Middle";
    case En::Side1: return "Side1";
    case En::Side2: return "Side2";
    default: std::unreachable();
    }
}
