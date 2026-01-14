#include <Keyboard/KeyCode.h>

#include <utility>

//======================================================================================================================
String keyboard::str(const keyboard::KeyCode code)
{
    using En = keyboard::KeyCode;

    switch (code) {
    case En::Unknown: return "KeyCode::Unknown";
    case En::Exclamation: return "KeyCode::Exclamation";
    case En::DoubleQuote: return "KeyCode::DoubleQuote";
    case En::Hash: return "KeyCode::Hash";
    case En::Dollar: return "KeyCode::Dollar";
    case En::Percent: return "KeyCode::Percent";
    case En::Ampersand: return "KeyCode::Ampersand";
    case En::Apostrophe: return "KeyCode::Apostrophe";
    case En::LeftRoundBracket: return "KeyCode::LeftRoundBracket";
    case En::RightRoundBracket: return "KeyCode::RightRoundBracket";
    case En::Asterisk: return "KeyCode::Asterisk";
    case En::Plus: return "KeyCode::Plus";
    case En::Comma: return "KeyCode::Comma";
    case En::Minus: return "KeyCode::Minus";
    case En::Dot: return "KeyCode::Dot";
    case En::Slash: return "KeyCode::Slash";
    case En::Num0: return "KeyCode::Num0";
    case En::Num1: return "KeyCode::Num1";
    case En::Num2: return "KeyCode::Num2";
    case En::Num3: return "KeyCode::Num3";
    case En::Num4: return "KeyCode::Num4";
    case En::Num5: return "KeyCode::Num5";
    case En::Num6: return "KeyCode::Num6";
    case En::Num7: return "KeyCode::Num7";
    case En::Num8: return "KeyCode::Num8";
    case En::Num9: return "KeyCode::Num9";
    case En::Colon: return "KeyCode::Colon";
    case En::Semicolon: return "KeyCode::Semicolon";
    case En::LessThan: return "KeyCode::LessThan";
    case En::Equal: return "KeyCode::Equal";
    case En::GreaterThan: return "KeyCode::GreaterThan";
    case En::Question: return "KeyCode::Question";
    case En::AtSign: return "KeyCode::AtSign";
    case En::A: return "KeyCode::A";
    case En::B: return "KeyCode::B";
    case En::C: return "KeyCode::C";
    case En::D: return "KeyCode::D";
    case En::E: return "KeyCode::E";
    case En::F: return "KeyCode::F";
    case En::G: return "KeyCode::G";
    case En::H: return "KeyCode::H";
    case En::I: return "KeyCode::I";
    case En::J: return "KeyCode::J";
    case En::K: return "KeyCode::K";
    case En::L: return "KeyCode::L";
    case En::M: return "KeyCode::M";
    case En::N: return "KeyCode::N";
    case En::O: return "KeyCode::O";
    case En::P: return "KeyCode::P";
    case En::Q: return "KeyCode::Q";
    case En::R: return "KeyCode::R";
    case En::S: return "KeyCode::S";
    case En::T: return "KeyCode::T";
    case En::U: return "KeyCode::U";
    case En::V: return "KeyCode::V";
    case En::W: return "KeyCode::W";
    case En::X: return "KeyCode::X";
    case En::Y: return "KeyCode::Y";
    case En::Z: return "KeyCode::Z";
    case En::LeftSquareBracket: return "KeyCode::LeftSquareBracket";
    case En::Backslash: return "KeyCode::Backslash";
    case En::RightSquareBracket: return "KeyCode::RightSquareBracket";
    case En::Caret: return "KeyCode::Caret";
    case En::Underscore: return "KeyCode::Underscore";
    case En::Backtick: return "KeyCode::Backtick";
    case En::LeftCurlyBracket: return "KeyCode::LeftCurlyBracket";
    case En::VerticalBar: return "KeyCode::VerticalBar";
    case En::RightCurlyBracket: return "KeyCode::RightCurlyBracket";
    case En::Tilde: return "KeyCode::Tilde";
    default: std::unreachable();
    }
}
