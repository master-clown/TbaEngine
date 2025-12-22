#pragma once

#include <Common/Memory.h>

//======================================================================================================================
namespace framework {
    class Framework;
}

//======================================================================================================================
namespace input {
    class Keyboard;
    class Mouse;
}

//======================================================================================================================
namespace input {
    //==================================================================================================================
    class DeviceMgr {
    public:
        explicit DeviceMgr(framework::Framework&);
        virtual ~DeviceMgr();

        //--------------------------------------------------------------------------------------------------------------
        void update();

        //--------------------------------------------------------------------------------------------------------------
        Keyboard& getKeyboard();
        const Keyboard& getKeyboard() const;

        Mouse& getMouse();
        const Mouse& getMouse() const;

    protected:
        framework::Framework& _getFramework();

        //--------------------------------------------------------------------------------------------------------------
        void _setKeyboard(uptr<Keyboard>);
        void _setMouse(uptr<Mouse>);

    private:
        framework::Framework& _framework;
        uptr<Keyboard> _keyboard;
        uptr<Mouse> _mouse;
    };
}
