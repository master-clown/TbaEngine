#include <Keyboard/KeyScancode.h>

#include <utility>

//======================================================================================================================
String keyboard::str(const keyboard::KeyScancode code)
{
    using En = keyboard::KeyScancode;

    switch (code) {
    case En::Unknown: return "KeyScancode::Unknown";
    case En::A: return "KeyScancode::A";
    case En::B: return "KeyScancode::B";
    case En::C: return "KeyScancode::C";
    case En::D: return "KeyScancode::D";
    case En::E: return "KeyScancode::E";
    case En::F: return "KeyScancode::F";
    case En::G: return "KeyScancode::G";
    case En::H: return "KeyScancode::H";
    case En::I: return "KeyScancode::I";
    case En::J: return "KeyScancode::J";
    case En::K: return "KeyScancode::K";
    case En::L: return "KeyScancode::L";
    case En::M: return "KeyScancode::M";
    case En::N: return "KeyScancode::N";
    case En::O: return "KeyScancode::O";
    case En::P: return "KeyScancode::P";
    case En::Q: return "KeyScancode::Q";
    case En::R: return "KeyScancode::R";
    case En::S: return "KeyScancode::S";
    case En::T: return "KeyScancode::T";
    case En::U: return "KeyScancode::U";
    case En::V: return "KeyScancode::V";
    case En::W: return "KeyScancode::W";
    case En::X: return "KeyScancode::X";
    case En::Y: return "KeyScancode::Y";
    case En::Z: return "KeyScancode::Z";
    case En::Num0: return "KeyScancode::Num0";
    case En::Num1: return "KeyScancode::Num1";
    case En::Num2: return "KeyScancode::Num2";
    case En::Num3: return "KeyScancode::Num3";
    case En::Num4: return "KeyScancode::Num4";
    case En::Num5: return "KeyScancode::Num5";
    case En::Num6: return "KeyScancode::Num6";
    case En::Num7: return "KeyScancode::Num7";
    case En::Num8: return "KeyScancode::Num8";
    case En::Num9: return "KeyScancode::Num9";
    case En::Enter: return "KeyScancode::Enter";
    case En::Escape: return "KeyScancode::Escape";
    case En::Backspace: return "KeyScancode::Backspace";
    case En::Tab: return "KeyScancode::Tab";
    case En::Space: return "KeyScancode::Space";
    case En::Apostrophe: return "KeyScancode::Apostrophe";
    case En::Comma: return "KeyScancode::Comma";
    case En::Minus: return "KeyScancode::Minus";
    case En::Dot: return "KeyScancode::Dot";
    case En::Slash: return "KeyScancode::Slash";
    case En::Semicolon: return "KeyScancode::Semicolon";
    case En::Equal: return "KeyScancode::Equal";
    case En::LeftSquareBracket: return "KeyScancode::LeftSquareBracket";
    case En::Backslash: return "KeyScancode::Backslash";
    case En::RightSquareBracket: return "KeyScancode::RightSquareBracket";
    case En::Backtick: return "KeyScancode::Backtick";
    case En::LCtrl: return "KeyScancode::LCtrl";
    case En::LShift: return "KeyScancode::LShift";
    case En::LAlt: return "KeyScancode::LAlt";
    case En::LGui: return "KeyScancode::LGui";
    case En::RCtrl: return "KeyScancode::RCtrl";
    case En::RShift: return "KeyScancode::RShift";
    case En::RAlt: return "KeyScancode::RAlt";
    case En::RGui: return "KeyScancode::RGui";
    default: std::unreachable();
    }
}
