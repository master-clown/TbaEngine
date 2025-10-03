#pragma once

#include <Winsys/Window.h>

#include <Common/Memory.h>

//======================================================================================================================
namespace winsys {
    class WindowMgr {
    public:
        virtual ~WindowMgr();

        virtual uptr<Window> createWindow(WindowOptions) = 0;
    };
}
