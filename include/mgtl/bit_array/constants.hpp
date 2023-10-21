#include <mgtl/type_traits/type_traits.hpp>
#pragma once

using namespace mgtl::type_traits;
namespace mgtl::bit_array::constants {
using _64_t = i_const_t<64>;
using _32_t = i_const_t<32>;
using _16_t = i_const_t<16>;
using _8_t = i_const_t<8>;

static constexpr auto _64 = i_const_v<64>;
static constexpr auto _32 = i_const_v<32>;
static constexpr auto _16 = i_const_v<16>;
static constexpr auto _8 = i_const_v<8>;
}// namespace mgtl::bit_array::constants
