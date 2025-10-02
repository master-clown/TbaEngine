#pragma once

#include <memory>

//======================================================================================================================
template <class T>
using uptr = std::unique_ptr<T>;

//----------------------------------------------------------------------------------------------------------------------
template <class T, class... Args>
uptr<T> makeUPtr(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}
