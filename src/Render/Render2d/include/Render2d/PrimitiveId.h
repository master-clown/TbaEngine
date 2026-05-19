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
        static constexpr uint8 _idBitOffset = 0;
        static constexpr uint8 _primitiveTypeBitOffset = 30;

        static constexpr RawId _primitiveTypeBitPattern = std::numeric_limits<RawId>::max() >> _primitiveTypeBitOffset;
        static constexpr uint8 _maxAvailablePrimitiveTypes = _primitiveTypeBitPattern + 1; // from zero

        static constexpr RawId _primitiveTypeMask = _primitiveTypeBitPattern << _primitiveTypeBitOffset;
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
