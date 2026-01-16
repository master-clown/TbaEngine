#pragma once

//======================================================================================================================
template <class FlagEnum>
inline constexpr bool isFlagEnum = false;

//======================================================================================================================
template <class FlagEnum>
concept FlagEnumConcept = requires {
    isFlagEnum<FlagEnum>;
};

//======================================================================================================================
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum operator&(const FlagEnum&, const FlagEnum&);

//----------------------------------------------------------------------------------------------------------------------
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum& operator&=(FlagEnum&, const FlagEnum&);

//======================================================================================================================
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum operator|(const FlagEnum&, const FlagEnum&);

//----------------------------------------------------------------------------------------------------------------------
template <FlagEnumConcept FlagEnum>
constexpr FlagEnum& operator|=(FlagEnum&, const FlagEnum&);
