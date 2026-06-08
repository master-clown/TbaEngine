#pragma once

#include <concepts>
#include <utility>

//======================================================================================================================
template <class T, auto onDestructionCallback>
    requires std::invocable<decltype(onDestructionCallback), const T&>
class RaiiWrapper final {
public:
    using ValueType = T;

    //==================================================================================================================
    explicit RaiiWrapper(ValueType&& value)
        : _value(std::move(value))
    {
    }

    ~RaiiWrapper()
    {
        onDestructionCallback(_value);
    }

    ValueType& getUnderlying()
    {
        return _value;
    }

    const ValueType& getUnderlying() const
    {
        return _value;
    }

    operator ValueType&()
    {
        return getUnderlying();
    }

    operator const ValueType&() const
    {
        return getUnderlying();
    }

private:
    ValueType _value;
};
