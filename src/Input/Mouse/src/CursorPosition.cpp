#include <Mouse/CursorPosition.h>

//======================================================================================================================
String mouse::str(const mouse::CursorPosition& pos)
{
    return strFormat("{{.x={},.y={}}}", pos.x, pos.y);
}
