#include "SdlKeyCode.h"

#include <Input/LogCategory.h>
#include <Logger/CategorizedLogging.h>

using namespace sdl_input;

//======================================================================================================================
keyboard::KeyCode sdl_input::fromSdlKeyCode(const SDL_Keycode code)
{
    using To = keyboard::KeyCode;

    switch (code) {
    case SDLK_UNKNOWN: return To::Unknown;
    case SDLK_RETURN: return To::Enter;
    case SDLK_ESCAPE: return To::Escape;
    case SDLK_BACKSPACE: return To::Backspace;
    case SDLK_TAB: return To::Tab;
    case SDLK_SPACE: return To::Space;
    case SDLK_EXCLAIM: return To::Exclamation;
    case SDLK_DBLAPOSTROPHE: return To::DoubleQuote;
    case SDLK_HASH: return To::Hash;
    case SDLK_DOLLAR: return To::Dollar;
    case SDLK_PERCENT: return To::Percent;
    case SDLK_AMPERSAND: return To::Ampersand;
    case SDLK_APOSTROPHE: return To::Apostrophe;
    case SDLK_LEFTPAREN: return To::LeftRoundBracket;
    case SDLK_RIGHTPAREN: return To::RightRoundBracket;
    case SDLK_ASTERISK: return To::Asterisk;
    case SDLK_PLUS: return To::Plus;
    case SDLK_COMMA: return To::Comma;
    case SDLK_MINUS: return To::Minus;
    case SDLK_PERIOD: return To::Dot;
    case SDLK_SLASH: return To::Slash;
    case SDLK_0: return To::Num0;
    case SDLK_1: return To::Num1;
    case SDLK_2: return To::Num2;
    case SDLK_3: return To::Num3;
    case SDLK_4: return To::Num4;
    case SDLK_5: return To::Num5;
    case SDLK_6: return To::Num6;
    case SDLK_7: return To::Num7;
    case SDLK_8: return To::Num8;
    case SDLK_9: return To::Num9;
    case SDLK_COLON: return To::Colon;
    case SDLK_SEMICOLON: return To::Semicolon;
    case SDLK_LESS: return To::LessThan;
    case SDLK_EQUALS: return To::Equal;
    case SDLK_GREATER: return To::GreaterThan;
    case SDLK_QUESTION: return To::Question;
    case SDLK_AT: return To::AtSign;
    case SDLK_A: return To::A;
    case SDLK_B: return To::B;
    case SDLK_C: return To::C;
    case SDLK_D: return To::D;
    case SDLK_E: return To::E;
    case SDLK_F: return To::F;
    case SDLK_G: return To::G;
    case SDLK_H: return To::H;
    case SDLK_I: return To::I;
    case SDLK_J: return To::J;
    case SDLK_K: return To::K;
    case SDLK_L: return To::L;
    case SDLK_M: return To::M;
    case SDLK_N: return To::N;
    case SDLK_O: return To::O;
    case SDLK_P: return To::P;
    case SDLK_Q: return To::Q;
    case SDLK_R: return To::R;
    case SDLK_S: return To::S;
    case SDLK_T: return To::T;
    case SDLK_U: return To::U;
    case SDLK_V: return To::V;
    case SDLK_W: return To::W;
    case SDLK_X: return To::X;
    case SDLK_Y: return To::Y;
    case SDLK_Z: return To::Z;
    case SDLK_LEFTBRACKET: return To::LeftSquareBracket;
    case SDLK_BACKSLASH: return To::Backslash;
    case SDLK_RIGHTBRACKET: return To::RightSquareBracket;
    case SDLK_CARET: return To::Caret;
    case SDLK_UNDERSCORE: return To::Underscore;
    case SDLK_GRAVE: return To::Backtick;
    case SDLK_LEFTBRACE: return To::LeftCurlyBracket;
    case SDLK_PIPE: return To::VerticalBar;
    case SDLK_RIGHTBRACE: return To::RightCurlyBracket;
    case SDLK_TILDE: return To::Tilde;
    case SDLK_CAPSLOCK: return To::CapsLock;
    case SDLK_F1: return To::F1;
    case SDLK_F2: return To::F2;
    case SDLK_F3: return To::F3;
    case SDLK_F4: return To::F4;
    case SDLK_F5: return To::F5;
    case SDLK_F6: return To::F6;
    case SDLK_F7: return To::F7;
    case SDLK_F8: return To::F8;
    case SDLK_F9: return To::F9;
    case SDLK_F10: return To::F10;
    case SDLK_F11: return To::F11;
    case SDLK_F12: return To::F12;
    case SDLK_PRINTSCREEN: return To::PrintScreen;
    case SDLK_INSERT: return To::Insert;
    case SDLK_DELETE: return To::Delete;
    case SDLK_HOME: return To::Home;
    case SDLK_PAGEUP: return To::PageUp;
    case SDLK_PAGEDOWN: return To::PageDown;
    case SDLK_END: return To::End;
    case SDLK_LEFT: return To::LeftArrow;
    case SDLK_RIGHT: return To::RightArrow;
    case SDLK_UP: return To::UpArrow;
    case SDLK_DOWN: return To::DownArrow;
    default: break;
    };

    LOG_CATEGORIZED(input::LogCategory::KeyCodeConversion,
                    logger::LogMessageLevel::Verbose,
                    "Unknown SDL_Keycode passed ({})",
                    static_cast<SDL_Keycode>(code)); // TODO: print str(code)

    return To::Unknown;
}

//======================================================================================================================
SDL_Keycode sdl_input::toSdlKeyCode(const keyboard::KeyCode code)
{
    using From = keyboard::KeyCode;

    switch (code) {
    case From::Unknown: return SDLK_UNKNOWN;
    case From::Enter: return SDLK_RETURN;
    case From::Escape: return SDLK_ESCAPE;
    case From::Backspace: return SDLK_BACKSPACE;
    case From::Tab: return SDLK_TAB;
    case From::Exclamation: return SDLK_EXCLAIM;
    case From::DoubleQuote: return SDLK_DBLAPOSTROPHE;
    case From::Hash: return SDLK_HASH;
    case From::Dollar: return SDLK_DOLLAR;
    case From::Percent: return SDLK_PERCENT;
    case From::Ampersand: return SDLK_AMPERSAND;
    case From::Apostrophe: return SDLK_APOSTROPHE;
    case From::LeftRoundBracket: return SDLK_LEFTPAREN;
    case From::RightRoundBracket: return SDLK_RIGHTPAREN;
    case From::Asterisk: return SDLK_ASTERISK;
    case From::Plus: return SDLK_PLUS;
    case From::Comma: return SDLK_COMMA;
    case From::Minus: return SDLK_MINUS;
    case From::Dot: return SDLK_PERIOD;
    case From::Slash: return SDLK_SLASH;
    case From::Num0: return SDLK_0;
    case From::Num1: return SDLK_1;
    case From::Num2: return SDLK_2;
    case From::Num3: return SDLK_3;
    case From::Num4: return SDLK_4;
    case From::Num5: return SDLK_5;
    case From::Num6: return SDLK_6;
    case From::Num7: return SDLK_7;
    case From::Num8: return SDLK_8;
    case From::Num9: return SDLK_9;
    case From::Colon: return SDLK_COLON;
    case From::Semicolon: return SDLK_SEMICOLON;
    case From::LessThan: return SDLK_LESS;
    case From::Equal: return SDLK_EQUALS;
    case From::GreaterThan: return SDLK_GREATER;
    case From::Question: return SDLK_QUESTION;
    case From::AtSign: return SDLK_AT;
    case From::A: return SDLK_A;
    case From::B: return SDLK_B;
    case From::C: return SDLK_C;
    case From::D: return SDLK_D;
    case From::E: return SDLK_E;
    case From::F: return SDLK_F;
    case From::G: return SDLK_G;
    case From::H: return SDLK_H;
    case From::I: return SDLK_I;
    case From::J: return SDLK_J;
    case From::K: return SDLK_K;
    case From::L: return SDLK_L;
    case From::M: return SDLK_M;
    case From::N: return SDLK_N;
    case From::O: return SDLK_O;
    case From::P: return SDLK_P;
    case From::Q: return SDLK_Q;
    case From::R: return SDLK_R;
    case From::S: return SDLK_S;
    case From::T: return SDLK_T;
    case From::U: return SDLK_U;
    case From::V: return SDLK_V;
    case From::W: return SDLK_W;
    case From::X: return SDLK_X;
    case From::Y: return SDLK_Y;
    case From::Z: return SDLK_Z;
    case From::LeftSquareBracket: return SDLK_LEFTBRACKET;
    case From::Backslash: return SDLK_BACKSLASH;
    case From::RightSquareBracket: return SDLK_RIGHTBRACKET;
    case From::Caret: return SDLK_CARET;
    case From::Underscore: return SDLK_UNDERSCORE;
    case From::Backtick: return SDLK_GRAVE;
    case From::LeftCurlyBracket: return SDLK_LEFTBRACE;
    case From::VerticalBar: return SDLK_PIPE;
    case From::RightCurlyBracket: return SDLK_RIGHTBRACE;
    case From::Tilde: return SDLK_TILDE;
    case From::CapsLock: return SDLK_CAPSLOCK;
    case From::F1: return SDLK_F1;
    case From::F2: return SDLK_F2;
    case From::F3: return SDLK_F3;
    case From::F4: return SDLK_F4;
    case From::F5: return SDLK_F5;
    case From::F6: return SDLK_F6;
    case From::F7: return SDLK_F7;
    case From::F8: return SDLK_F8;
    case From::F9: return SDLK_F9;
    case From::F10: return SDLK_F10;
    case From::F11: return SDLK_F11;
    case From::F12: return SDLK_F12;
    case From::PrintScreen: return SDLK_PRINTSCREEN;
    case From::Insert: return SDLK_INSERT;
    case From::Delete: return SDLK_DELETE;
    case From::Home: return SDLK_HOME;
    case From::PageUp: return SDLK_PAGEUP;
    case From::PageDown: return SDLK_PAGEDOWN;
    case From::End: return SDLK_END;
    case From::LeftArrow: return SDLK_LEFT;
    case From::RightArrow: return SDLK_RIGHT;
    case From::UpArrow: return SDLK_UP;
    case From::DownArrow: return SDLK_DOWN;
    default: break;
    };

    LOG_CATEGORIZED(input::LogCategory::KeyCodeConversion,
                    logger::LogMessageLevel::Verbose,
                    "Unknown keyboard::KeyCode passed ({})",
                    static_cast<std::underlying_type_t<From>>(code)); // TODO: print str(code)

    return SDLK_UNKNOWN;
}
