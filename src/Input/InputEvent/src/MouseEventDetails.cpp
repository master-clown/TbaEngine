#include <InputEvent/MouseEventDetails.h>

//======================================================================================================================
using namespace input_event;

//======================================================================================================================
String input_event::str(const MouseEventDetails<MouseEventKind::ButtonDown>& evDetail)
{
    return strFormat("MouseEvent<ButtonDown>{{.btn={},.keyMods={}}}",
                     str(evDetail.button),
                     str(evDetail.keyboardMods));
}

//======================================================================================================================
String input_event::str(const MouseEventDetails<MouseEventKind::ButtonUp>& evDetail)
{
    return strFormat("MouseEvent<ButtonUp>{{.btn={},.keyMods={}}}",
                     str(evDetail.button),
                     str(evDetail.keyboardMods));
}

//======================================================================================================================
String input_event::str(const MouseEventDetails<MouseEventKind::MouseMoved>& evDetail)
{
    return strFormat("MouseEvent<MouseMoved>{{.pos={},.delta={},.pressedBtn={}}}",
                     str(evDetail.cursorPos),
                     str(evDetail.cursorPosDelta),
                     str(evDetail.pressedButton));
}

//======================================================================================================================
String input_event::str(const MouseEventDetails<MouseEventKind::WheelMoved>& evDetail)
{
    return strFormat("MouseEvent<WheelMoved>{{.xOffset={},.yOffset={}}}", evDetail.x, evDetail.y);
}
