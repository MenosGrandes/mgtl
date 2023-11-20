#include <functional>
#include <limits>
#include <type_traits>

#pragma once

namespace mgtl::type_traits {
template<typename T, T NUMBER_OF_BITS> using integral_const_t = std::integral_constant<T, NUMBER_OF_BITS>;
template<typename T, T NUMBER_OF_BITS> static constexpr T integral_const_v = integral_const_t<T, NUMBER_OF_BITS>::value;


template<std::size_t NUMBER_OF_BITS> using i_const_t = integral_const_t<std::size_t, NUMBER_OF_BITS>;
template<std::size_t NUMBER_OF_BITS>
static constexpr std::size_t i_const_v = integral_const_t<std::size_t, NUMBER_OF_BITS>::value;


template<typename T> using _zero_t = integral_const_t<T, 0>;


static constexpr auto _0_v = i_const_v<0>;
static constexpr auto true_v = std::true_type::value;
static constexpr auto false_v = std::false_type::value;

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
template<typename T, std::size_t NUMBER_OF_BITS>
static constexpr auto is_integer_but_not_zero_v = is_integer_but_not_zero_t<T, NUMBER_OF_BITS>::value;


template<bool _Cond, class Enabler = void> struct is_true_t : std::false_type
{
};

template<bool _Cond> struct is_true_t<_Cond, std::enable_if_t<_Cond>> : std::true_type
{
};

template<bool _Cond> static constexpr auto is_true_v = is_true_t<_Cond>::value;


template<bool _Cond, class Enabler = void> struct is_false_t : std::false_type
{
};

template<bool _Cond> struct is_false_t<_Cond, std::enable_if_t<!_Cond>> : std::true_type
{
};

template<bool _Cond> static constexpr auto is_false_v = is_false_t<_Cond>::value;

template<typename T> static constexpr auto digits_v = std::numeric_limits<T>::digits;
constexpr auto _digits_u = digits_v<unsigned>;
constexpr auto _digits_l = digits_v<unsigned long>;
constexpr auto _digits_ll = digits_v<unsigned long long>;

template<class F, class S, class Enabler = void> struct is_less_t : std::false_type
{
};


template<class F, class S> struct is_less_t<F, S, typename std::enable_if_t<(F::value < S::value)>> : std::true_type
{
};

template<class F, class S> static constexpr auto is_less_v = is_less_t<F, S>::value;




}// namespace mgtl::type_traits
