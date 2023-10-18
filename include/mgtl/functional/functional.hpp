#pragma once
#include <functional>


namespace mgtl::functional
{
template<std::size_t N> using i_const_t = std::integral_constant<std::size_t, N>;
template<std::size_t N> static constexpr std::size_t i_const_v = i_const_t<N>::value;
using _zero = i_const_t<0>;
static constexpr auto _0_v = i_const_v<0>;

static constexpr auto is_true_v = std::true_type::value;
static constexpr auto is_false_v = std::false_type::value;

template<typename T, typename U> using is_not_same_t = std::negation<std::is_same<T, U>>;

template<typename T, typename U> static constexpr auto is_not_same_v = is_not_same_t<T, U>::value;

template<std::size_t V, class Enable = void> struct is_integer_but_not_zero_t : public std::false_type
{
};

template<std::size_t V>
struct is_integer_but_not_zero_t<V, typename std::enable_if_t<is_not_same_v<i_const_t<V>, _zero>>>
  : public std::true_type
{
};

template<std::size_t N> static constexpr auto is_integer_but_not_zero_v = is_integer_but_not_zero_t<N>::value;

  template<typename...> struct is_one_of : std::false_type
  {
  };


  template<typename... T> static constexpr auto is_one_of_v = is_one_of<T...>::value;
  template<typename F, typename S, typename... T> struct is_one_of<F, S, T...>
  {
    static constexpr bool value = std::is_same_v<F, S> || is_one_of_v<F, T...>;
  };

}
