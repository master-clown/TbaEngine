#include "SdlKeyScancode.h"

#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>

using namespace sdl_input;

//======================================================================================================================
SDL_Scancode toSdlKeyScancode(const input::KeyScancode scancode)
{
    using En = input::KeyScancode;

    switch (scancode) {
    case En::Unknown: return SDL_SCANCODE_UNKNOWN;
    case En::A: return SDL_SCANCODE_A;
    case En::B: return SDL_SCANCODE_B;
    case En::C: return SDL_SCANCODE_C;
    case En::D: return SDL_SCANCODE_D;
    case En::E: return SDL_SCANCODE_E;
    case En::F: return SDL_SCANCODE_F;
    case En::G: return SDL_SCANCODE_G;
    case En::H: return SDL_SCANCODE_H;
    case En::I: return SDL_SCANCODE_I;
    case En::J: return SDL_SCANCODE_J;
    case En::K: return SDL_SCANCODE_K;
    case En::L: return SDL_SCANCODE_L;
    case En::M: return SDL_SCANCODE_M;
    case En::N: return SDL_SCANCODE_N;
    case En::O: return SDL_SCANCODE_O;
    case En::P: return SDL_SCANCODE_P;
    case En::Q: return SDL_SCANCODE_Q;
    case En::R: return SDL_SCANCODE_R;
    case En::S: return SDL_SCANCODE_S;
    case En::T: return SDL_SCANCODE_T;
    case En::U: return SDL_SCANCODE_U;
    case En::V: return SDL_SCANCODE_V;
    case En::W: return SDL_SCANCODE_W;
    case En::X: return SDL_SCANCODE_X;
    case En::Y: return SDL_SCANCODE_Y;
    case En::Z: return SDL_SCANCODE_Z;
    case En::Num0: return SDL_SCANCODE_0;
    case En::Num1: return SDL_SCANCODE_1;
    case En::Num2: return SDL_SCANCODE_2;
    case En::Num3: return SDL_SCANCODE_3;
    case En::Num4: return SDL_SCANCODE_4;
    case En::Num5: return SDL_SCANCODE_5;
    case En::Num6: return SDL_SCANCODE_6;
    case En::Num7: return SDL_SCANCODE_7;
    case En::Num8: return SDL_SCANCODE_8;
    case En::Num9: return SDL_SCANCODE_9;
    case En::Enter: return SDL_SCANCODE_RETURN;
    case En::Escape: return SDL_SCANCODE_ESCAPE;
    case En::Backspace: return SDL_SCANCODE_BACKSPACE;
    case En::Tab: return SDL_SCANCODE_TAB;
    case En::Space: return SDL_SCANCODE_SPACE;
    case En::Apostrophe: return SDL_SCANCODE_APOSTROPHE;
    case En::Comma: return SDL_SCANCODE_COMMA;
    case En::Minus: return SDL_SCANCODE_MINUS;
    case En::Dot: return SDL_SCANCODE_PERIOD;
    case En::Slash: return SDL_SCANCODE_SLASH;
    case En::Semicolon: return SDL_SCANCODE_SEMICOLON;
    case En::Equal: return SDL_SCANCODE_EQUALS;
    case En::LeftSquareBracket: return SDL_SCANCODE_LEFTBRACKET;
    case En::Backslash: return SDL_SCANCODE_BACKSLASH;
    case En::RightSquareBracket: return SDL_SCANCODE_RIGHTBRACKET;
    case En::Backtick: return SDL_SCANCODE_GRAVE;
    case En::LCtrl: return SDL_SCANCODE_LCTRL;
    case En::LShift: return SDL_SCANCODE_LSHIFT;
    case En::LAlt: return SDL_SCANCODE_LALT;
    case En::LGui: return SDL_SCANCODE_LGUI;
    case En::RCtrl: return SDL_SCANCODE_RCTRL;
    case En::RShift: return SDL_SCANCODE_RSHIFT;
    case En::RAlt: return SDL_SCANCODE_RALT;
    case En::RGui: return SDL_SCANCODE_RGUI;
    default: break;
    }

    LOG_CATEGORIZED(input::LogCategory::KeyScancodeConversion,
                    logger::LogMessageLevel::Verbose,
                    "Unknown input::KeyScancode passed ({})",
                    static_cast<std::underlying_type_t<input::KeyScancode>>(scancode)); // TODO: print str(code)

    return SDL_SCANCODE_UNKNOWN;
}
