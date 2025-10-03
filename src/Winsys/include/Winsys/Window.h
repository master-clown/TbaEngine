#pragma once

#include <Winsys/WindowOptions.h>

//======================================================================================================================
namespace winsys {
    class Window {
    public:
        explicit Window(WindowOptions);
        virtual ~Window();

        const WindowOptions& getWindowOptions() const;

    private:
        WindowOptions _windowOptions;
    };
}
