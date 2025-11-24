#pragma once

//======================================================================================================================
// For `std::visit(OverloadMultiplexor{[](int){...}, [](string){...}}, someVariant)`
template <class... Callable>
struct OverloadMultiplexor final : Callable... {
    using Callable::operator()...;
};

//----------------------------------------------------------------------------------------------------------------------
template <class... Callable>
OverloadMultiplexor(Callable...) -> OverloadMultiplexor<Callable...>;
