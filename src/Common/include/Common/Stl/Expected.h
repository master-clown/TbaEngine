#pragma once

#include <expected>

//======================================================================================================================
template <class T, class Unexpected>
using Expected = std::expected<T, Unexpected>;
