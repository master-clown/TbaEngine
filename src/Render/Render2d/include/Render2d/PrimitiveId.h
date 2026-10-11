#pragma once

#include <Common/Integers.h>

#include <atomic>
#include <climits>
#include <functional>
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
        constexpr RawId getRawId() const noexcept;
        constexpr operator RawId() const noexcept;

        //--------------------------------------------------------------------------------------------------------------
        enum class PrimitiveType : RawId {
            Point = 0,
            Line = 1,
            Trinangle = 2,
        };
        constexpr PrimitiveType getTypePart() const noexcept;

        using IdPart = RawId;
        constexpr IdPart getIdPart() const noexcept;

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
    constexpr auto PrimitiveId::getRawId() const noexcept -> RawId
    {
        return _rawId;
    }

    //==================================================================================================================
    constexpr PrimitiveId::operator RawId() const noexcept
    {
        return getRawId();
    }

    //==================================================================================================================
    constexpr auto PrimitiveId::getTypePart() const noexcept -> PrimitiveType
    {
        return static_cast<PrimitiveType>((getRawId() & _primitiveTypeMask) >> _bitOffsetForPrimitiveType);
    }

    //==================================================================================================================
    constexpr auto PrimitiveId::getIdPart() const noexcept -> IdPart
    {
        return getRawId() & _idMask;
    }

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

//==================================================================================================================
template <>
struct std::hash<render_2d::PrimitiveId> {
    constexpr std::size_t operator()(const render_2d::PrimitiveId& primId) const noexcept
    {
        return std::hash<render_2d::PrimitiveId::RawId>{}(primId.getRawId());
    }
};
