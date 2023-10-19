#include <functional>
#include <type_traits>

#pragma once

namespace mgtl::type_traits
{
template<typename T, T N> using integral_const_t = std::integral_constant<T, N>;
template<typename T, T N> static constexpr T integral_const_v = integral_const_t<T, N>::value;


template<std::size_t N> using i_const_t = integral_const_t<std::size_t, N>;
template<std::size_t N> static constexpr std::size_t i_const_v = integral_const_t<std::size_t, N>::value;


template<typename T> using _zero_t = integral_const_t<T, 0>;


static constexpr auto _0_v = i_const_v<0>;

static constexpr auto is_true_v = std::true_type::value;
static constexpr auto is_false_v = std::false_type::value;

template<typename T, typename U> using is_not_same_t = std::negation<std::is_same<T, U>>;

template<typename T, typename U> static constexpr auto is_not_same_v = is_not_same_t<T, U>::value;


template<typename...> struct is_one_of : std::false_type
{
};


template<typename... T> static constexpr auto is_one_of_v = is_one_of<T...>::value;
template<typename F, typename S, typename... T> struct is_one_of<F, S, T...>
{
  static constexpr bool value = std::is_same_v<F, S> || is_one_of_v<F, T...>;
};

template<typename...> struct and_t : std::true_type
{
};

template<typename T> struct and_t<T> : T
{
};

template<typename... T> static constexpr auto and_v = and_t<T...>::value;
template<typename T, typename... Tn> struct and_t<T, Tn...> : std::conditional_t<bool(T::value), and_t<Tn...>, T>
{
};

template<typename T> struct type_is
{
  using type = T;
};

template<typename V, V value, class Enable = void> struct is_integer_but_not_zero_t : public std::false_type
{
};
template<typename V, V value>
struct is_integer_but_not_zero_t<V,
  value,
  typename std::enable_if_t<is_not_same_v<integral_const_t<V, value>, _zero_t<V>>>> : public std::true_type
{
};
template<typename T, std::size_t N>
static constexpr auto is_integer_but_not_zero_v = is_integer_but_not_zero_t<T, N>::value;


template <bool _Cond, class Enabler = void>
struct is_true : std::false_type{};

template <bool _Cond>
struct is_true<_Cond, std::enable_if_t<_Cond>> : std::true_type{};



template <bool _Cond, class Enabler = void>
struct  is_false: std::false_type{};

template <bool _Cond>
struct is_false<_Cond, std::enable_if_t<!_Cond>> : std::true_type{};

}
