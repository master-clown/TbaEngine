#pragma once

#include <Common/Integers.h>

#include <atomic>
#include <numeric>

//======================================================================================================================
namespace render_2d {
    //==================================================================================================================
    class PrimitiveId final {
    public:
        using RawId = uint32;

        //--------------------------------------------------------------------------------------------------------------
        PrimitiveId() = delete;

        //--------------------------------------------------------------------------------------------------------------
        RawId getRawId() const;
        operator RawId() const;

        //--------------------------------------------------------------------------------------------------------------
        template <class Geometry2d>
        static PrimitiveId generate();

    private:
        RawId _rawId = 0;

        //--------------------------------------------------------------------------------------------------------------
        explicit PrimitiveId(RawId);

        static PrimitiveId _generateNewId(RawId primitiveType);

        //--------------------------------------------------------------------------------------------------------------
        static constexpr uint8 _bitOffsetForId = 0;
        static constexpr uint8 _numOfBitsForPrimitiveType = 2;
        static constexpr uint8 _bitOffsetForPrimitiveType = CHAR_BIT * sizeof(RawId) - _numOfBitsForPrimitiveType;

        static constexpr uint8 _numOfAvailablePrimitiveTypes = 1 << _numOfBitsForPrimitiveType;
        static constexpr uint8 _bitPatternForPrimitiveType = (1 << _numOfBitsForPrimitiveType) - 1;

        static constexpr RawId _primitiveTypeMask = _bitPatternForPrimitiveType << _bitOffsetForPrimitiveType;
        static constexpr RawId _idMask = ~_primitiveTypeMask;

        static void _staticAssertsForInvariants();

        //--------------------------------------------------------------------------------------------------------------
        static std::atomic<RawId> _nextId;
    };

    //==================================================================================================================
    constexpr bool operator==(const PrimitiveId lhs, const PrimitiveId rhs) noexcept
    {
        return lhs.getRawId() == rhs.getRawId();
    }

    //------------------------------------------------------------------------------------------------------------------
    constexpr bool operator!=(const PrimitiveId lhs, const PrimitiveId rhs) noexcept
    {
        return lhs.getRawId() != rhs.getRawId();
    }
}
