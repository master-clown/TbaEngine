#include <Render2d/VertexInfo.h>

#include <type_traits>

//======================================================================================================================
static_assert(std::is_default_constructible_v<render_2d::VertexInfo>);
static_assert(std::is_trivially_copy_constructible_v<render_2d::VertexInfo>);
static_assert(std::is_trivially_move_constructible_v<render_2d::VertexInfo>);
static_assert(std::is_standard_layout_v<render_2d::VertexInfo>);
