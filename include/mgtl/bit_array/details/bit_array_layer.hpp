
#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/bit_array/bit_manipulator.hpp>
#include <mgtl/bit_array/bit_size.hpp>
#include <mgtl/bit_array/details/bit_array_different_size.hpp>
#include <mgtl/bit_array/type_traits.hpp>
#include <mgtl/type_traits/type_traits.hpp>

#pragma once

using namespace mgtl::type_traits;
using namespace mgtl::bit_array::bite_size;
namespace mgtl::bit_array::details {

template<size_type NUMBER_OF_BITS_IN_LAYER, typename memory_t>
class _BitArrayLayer_t : public _BitArrayDifferentSize_t<NUMBER_OF_BITS_IN_LAYER, memory_t>
{
};
/*
 *
 *  There are 4 layers to represent set bits
 *
 * */
template<std::size_t NUMBER_OF_BITS_OVERALL, typename memory_t>
class BitArrayWithLayers_t : public _BitArrayDifferentSize_t<NUMBER_OF_BITS_OVERALL, memory_t>
{

public:
  using base_1 = typename base::_BitArrayBase_t<NUMBER_OF_BITS_OVERALL, memory_t>;
  using base_2 = typename base_1::bite_size_base;
  using base_1::size;
  using raw_memory_t = std::array<memory_t, base_2::memory_size_v>;

  template<std::size_t _NUMBER_OF_BITS, typename _memory_t>
  friend std::ostream &operator<<(std::ostream &, const BitArrayWithLayers_t<_NUMBER_OF_BITS, _memory_t> &);


  constexpr void set(size_type bit)
  {
    {
      auto [index, element] = get_element(bit);
      this->_layer_0[index] = base_1::BitManipulatorImpl::set(element, this->_layer_0[index]);
    }
  }
  constexpr auto get(size_type bit) const -> bool
  {
    auto [index, element] = get_element(bit);
    return base_1::BitManipulatorImpl::get(element, this->_layer_0[index]);
  }
  constexpr auto operator[](size_type bit) const -> bool { return get(bit); }
  constexpr auto clear(size_type bit) -> void
  {
    auto [index, element] = get_element(bit);
    this->_layer_0[index] = base_1::BitManipulatorImpl::clear(element, this->_layer_0[index]);
  }
  constexpr auto popcount()
  {
    // MenosGrandes std::accumulate?
    size_type counter{ 0 };
    for (memory_t i : _layer_0) {
      // for (size_type i = 0; i < base_2::memory_size_whole_v; i++) {
      counter += base_1::BitManipulatorImpl::popcount(i);
    }
    return counter;
  }

  constexpr auto fill() -> void
  {
    for (size_type i = 0; i < this->_data.size(); ++i) { _layer_0[i] = memory_t{}; }
  }
  static constexpr auto get_element(size_type bit) -> std::tuple<size_type, size_type>
  {
    const size_type index = static_cast<size_type>(bit / base_1::memory_t_digits);
    const size_type element = static_cast<size_type>((bit + base_1::memory_t_digits * index) % base_1::memory_t_digits);
    return { index, element };
  }

  enum class Layer_e { ONE = 4, TWO = 16, TREE = 64 };
  alignas(memory_t) raw_memory_t _layer_0;// uint8
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL / static_cast<size_type>(Layer_e::ONE), memory_t> _layer_1;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL / static_cast<size_type>(Layer_e::TWO), memory_t> _layer_2;
  alignas(memory_t) _BitArrayLayer_t<NUMBER_OF_BITS_OVERALL / static_cast<size_type>(Layer_e::TREE), memory_t> _layer_3;


  static constexpr auto map_to_layer([[maybe_unused]] size_type bit, Layer_e layer) -> size_type
  {

    switch (layer) {

    case Layer_e::ONE: {
      return 1;
    }
    case Layer_e::TWO: {
      return 2;
    }
    case Layer_e::TREE: {
      return 3;
    }
    case Layer_e::FOUR: {
      return 4;
    }
    }
  }
};


}// namespace mgtl::bit_array::details
