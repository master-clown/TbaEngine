#include "SdlKeyScancode.h"

#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>

using namespace sdl_input;

//======================================================================================================================
keyboard::KeyScancode fromSdlKeyScancode(const SDL_Scancode scancode)
{
    using From = SDL_Scancode;
    using To = keyboard::KeyScancode;

    switch (scancode) {
    case From::SDL_SCANCODE_UNKNOWN: return To::Unknown;
    case From::SDL_SCANCODE_A: return To::A;
    case From::SDL_SCANCODE_B: return To::B;
    case From::SDL_SCANCODE_C: return To::C;
    case From::SDL_SCANCODE_D: return To::D;
    case From::SDL_SCANCODE_E: return To::E;
    case From::SDL_SCANCODE_F: return To::F;
    case From::SDL_SCANCODE_G: return To::G;
    case From::SDL_SCANCODE_H: return To::H;
    case From::SDL_SCANCODE_I: return To::I;
    case From::SDL_SCANCODE_J: return To::J;
    case From::SDL_SCANCODE_K: return To::K;
    case From::SDL_SCANCODE_L: return To::L;
    case From::SDL_SCANCODE_M: return To::M;
    case From::SDL_SCANCODE_N: return To::N;
    case From::SDL_SCANCODE_O: return To::O;
    case From::SDL_SCANCODE_P: return To::P;
    case From::SDL_SCANCODE_Q: return To::Q;
    case From::SDL_SCANCODE_R: return To::R;
    case From::SDL_SCANCODE_S: return To::S;
    case From::SDL_SCANCODE_T: return To::T;
    case From::SDL_SCANCODE_U: return To::U;
    case From::SDL_SCANCODE_V: return To::V;
    case From::SDL_SCANCODE_W: return To::W;
    case From::SDL_SCANCODE_X: return To::X;
    case From::SDL_SCANCODE_Y: return To::Y;
    case From::SDL_SCANCODE_Z: return To::Z;
    case From::SDL_SCANCODE_0: return To::Num0;
    case From::SDL_SCANCODE_1: return To::Num1;
    case From::SDL_SCANCODE_2: return To::Num2;
    case From::SDL_SCANCODE_3: return To::Num3;
    case From::SDL_SCANCODE_4: return To::Num4;
    case From::SDL_SCANCODE_5: return To::Num5;
    case From::SDL_SCANCODE_6: return To::Num6;
    case From::SDL_SCANCODE_7: return To::Num7;
    case From::SDL_SCANCODE_8: return To::Num8;
    case From::SDL_SCANCODE_9: return To::Num9;
    case From::SDL_SCANCODE_RETURN: return To::Enter;
    case From::SDL_SCANCODE_ESCAPE: return To::Escape;
    case From::SDL_SCANCODE_BACKSPACE: return To::Backspace;
    case From::SDL_SCANCODE_TAB: return To::Tab;
    case From::SDL_SCANCODE_SPACE: return To::Space;
    case From::SDL_SCANCODE_APOSTROPHE: return To::Apostrophe;
    case From::SDL_SCANCODE_COMMA: return To::Comma;
    case From::SDL_SCANCODE_MINUS: return To::Minus;
    case From::SDL_SCANCODE_PERIOD: return To::Dot;
    case From::SDL_SCANCODE_SLASH: return To::Slash;
    case From::SDL_SCANCODE_SEMICOLON: return To::Semicolon;
    case From::SDL_SCANCODE_EQUALS: return To::Equal;
    case From::SDL_SCANCODE_LEFTBRACKET: return To::LeftSquareBracket;
    case From::SDL_SCANCODE_BACKSLASH: return To::Backslash;
    case From::SDL_SCANCODE_RIGHTBRACKET: return To::RightSquareBracket;
    case From::SDL_SCANCODE_GRAVE: return To::Backtick;
    case From::SDL_SCANCODE_LCTRL: return To::LCtrl;
    case From::SDL_SCANCODE_LSHIFT: return To::LShift;
    case From::SDL_SCANCODE_LALT: return To::LAlt;
    case From::SDL_SCANCODE_LGUI: return To::LGui;
    case From::SDL_SCANCODE_RCTRL: return To::RCtrl;
    case From::SDL_SCANCODE_RSHIFT: return To::RShift;
    case From::SDL_SCANCODE_RALT: return To::RAlt;
    case From::SDL_SCANCODE_RGUI: return To::RGui;
    default: break;
    }

    LOG_CATEGORIZED(input::LogCategory::KeyScancodeConversion,
                    logger::LogMessageLevel::Verbose,
                    "Unknown SDL_Scancode passed ({})",
                    static_cast<std::underlying_type_t<From>>(scancode)); // TODO: print str(code)

    return To::Unknown;
}

//======================================================================================================================
SDL_Scancode toSdlKeyScancode(const keyboard::KeyScancode scancode)
{
    using From = keyboard::KeyScancode;

    switch (scancode) {
    case From::Unknown: return SDL_SCANCODE_UNKNOWN;
    case From::A: return SDL_SCANCODE_A;
    case From::B: return SDL_SCANCODE_B;
    case From::C: return SDL_SCANCODE_C;
    case From::D: return SDL_SCANCODE_D;
    case From::E: return SDL_SCANCODE_E;
    case From::F: return SDL_SCANCODE_F;
    case From::G: return SDL_SCANCODE_G;
    case From::H: return SDL_SCANCODE_H;
    case From::I: return SDL_SCANCODE_I;
    case From::J: return SDL_SCANCODE_J;
    case From::K: return SDL_SCANCODE_K;
    case From::L: return SDL_SCANCODE_L;
    case From::M: return SDL_SCANCODE_M;
    case From::N: return SDL_SCANCODE_N;
    case From::O: return SDL_SCANCODE_O;
    case From::P: return SDL_SCANCODE_P;
    case From::Q: return SDL_SCANCODE_Q;
    case From::R: return SDL_SCANCODE_R;
    case From::S: return SDL_SCANCODE_S;
    case From::T: return SDL_SCANCODE_T;
    case From::U: return SDL_SCANCODE_U;
    case From::V: return SDL_SCANCODE_V;
    case From::W: return SDL_SCANCODE_W;
    case From::X: return SDL_SCANCODE_X;
    case From::Y: return SDL_SCANCODE_Y;
    case From::Z: return SDL_SCANCODE_Z;
    case From::Num0: return SDL_SCANCODE_0;
    case From::Num1: return SDL_SCANCODE_1;
    case From::Num2: return SDL_SCANCODE_2;
    case From::Num3: return SDL_SCANCODE_3;
    case From::Num4: return SDL_SCANCODE_4;
    case From::Num5: return SDL_SCANCODE_5;
    case From::Num6: return SDL_SCANCODE_6;
    case From::Num7: return SDL_SCANCODE_7;
    case From::Num8: return SDL_SCANCODE_8;
    case From::Num9: return SDL_SCANCODE_9;
    case From::Enter: return SDL_SCANCODE_RETURN;
    case From::Escape: return SDL_SCANCODE_ESCAPE;
    case From::Backspace: return SDL_SCANCODE_BACKSPACE;
    case From::Tab: return SDL_SCANCODE_TAB;
    case From::Space: return SDL_SCANCODE_SPACE;
    case From::Apostrophe: return SDL_SCANCODE_APOSTROPHE;
    case From::Comma: return SDL_SCANCODE_COMMA;
    case From::Minus: return SDL_SCANCODE_MINUS;
    case From::Dot: return SDL_SCANCODE_PERIOD;
    case From::Slash: return SDL_SCANCODE_SLASH;
    case From::Semicolon: return SDL_SCANCODE_SEMICOLON;
    case From::Equal: return SDL_SCANCODE_EQUALS;
    case From::LeftSquareBracket: return SDL_SCANCODE_LEFTBRACKET;
    case From::Backslash: return SDL_SCANCODE_BACKSLASH;
    case From::RightSquareBracket: return SDL_SCANCODE_RIGHTBRACKET;
    case From::Backtick: return SDL_SCANCODE_GRAVE;
    case From::LCtrl: return SDL_SCANCODE_LCTRL;
    case From::LShift: return SDL_SCANCODE_LSHIFT;
    case From::LAlt: return SDL_SCANCODE_LALT;
    case From::LGui: return SDL_SCANCODE_LGUI;
    case From::RCtrl: return SDL_SCANCODE_RCTRL;
    case From::RShift: return SDL_SCANCODE_RSHIFT;
    case From::RAlt: return SDL_SCANCODE_RALT;
    case From::RGui: return SDL_SCANCODE_RGUI;
    default: break;
    }

    LOG_CATEGORIZED(input::LogCategory::KeyScancodeConversion,
                    logger::LogMessageLevel::Verbose,
                    "Unknown keyboard::KeyScancode passed ({})",
                    static_cast<std::underlying_type_t<From>>(scancode)); // TODO: print str(code)

    return SDL_SCANCODE_UNKNOWN;
}
