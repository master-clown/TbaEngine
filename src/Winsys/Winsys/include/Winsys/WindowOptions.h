#pragma once

#include <Common/Stl/Optional.h>
#include <Common/String.h>
#include <RendererContext/RendererType.h>

#include <cstdint>

//======================================================================================================================
namespace winsys {
    struct WindowOptions final {
        String wndTitle;
        uint16_t wndWidth = 0;
        uint16_t wndHeight = 0;
        Optional<renderer_context::RendererType> initForRendererOfType = {};
    };
}
