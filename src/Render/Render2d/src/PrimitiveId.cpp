#include <Render2d/PrimitiveId.h>

//======================================================================================================================
using render_2d::PrimitiveId;

//======================================================================================================================
std::atomic<PrimitiveId::RawId> PrimitiveId::_nextId = 0;

//======================================================================================================================
void PrimitiveId::_staticAssertsForInvariants()
{
    static_assert(std::is_unsigned_v<RawId>);

    static_assert(_bitOffsetForId < CHAR_BIT * sizeof(RawId));
    static_assert(_bitOffsetForPrimitiveType + _numOfBitsForPrimitiveType <= CHAR_BIT * sizeof(RawId));

    static_assert((_primitiveTypeMask & _idMask) == 0);
    static_assert((_primitiveTypeMask | _idMask) == std::numeric_limits<RawId>::max());
}

//======================================================================================================================
auto PrimitiveId::getRawId() const -> RawId
{
    return _rawId;
}

//----------------------------------------------------------------------------------------------------------------------
PrimitiveId::operator RawId() const
{
    return getRawId();
}

//======================================================================================================================
PrimitiveId::PrimitiveId(RawId rawId)
    : _rawId(rawId)
{
}

//======================================================================================================================
namespace geometry_2d {
    struct Point2d;
    struct Line;
    struct Triangle;
}

//----------------------------------------------------------------------------------------------------------------------
auto PrimitiveId::_generateNewId(const RawId primitiveType) -> PrimitiveId
{
    const auto typePart = primitiveType << _bitOffsetForPrimitiveType;
    const auto idPart = PrimitiveId::_nextId.fetch_add(1) & _idMask;

    return PrimitiveId{typePart | idPart};
}

//----------------------------------------------------------------------------------------------------------------------
template <>
PrimitiveId PrimitiveId::generate<geometry_2d::Point2d>()
{
    static constexpr RawId typeIdx = 0;
    static_assert(typeIdx < _numOfAvailablePrimitiveTypes);

    return PrimitiveId::_generateNewId(typeIdx);
}

//----------------------------------------------------------------------------------------------------------------------
template <>
PrimitiveId PrimitiveId::generate<geometry_2d::Line>()
{
    static constexpr RawId typeIdx = 1;
    static_assert(typeIdx < _numOfAvailablePrimitiveTypes);

    return PrimitiveId::_generateNewId(typeIdx);
}

//----------------------------------------------------------------------------------------------------------------------
template <>
PrimitiveId PrimitiveId::generate<geometry_2d::Triangle>()
{
    static constexpr RawId typeIdx = 2;
    static_assert(typeIdx < _numOfAvailablePrimitiveTypes);

    return PrimitiveId::_generateNewId(typeIdx);
}
