#include <functional>
#include <type_traits>


#pragma once
namespace mgtl::functional {
constexpr bool is_less(auto F, auto S) { return F < S; }
constexpr bool is_equal(auto F, auto S) { return F == S; }
constexpr bool is_less_and_equal(auto F, auto S) { return F <= S; }

}// namespace mgtl::functional
