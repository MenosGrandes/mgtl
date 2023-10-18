#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include <mgtl/functional/functional.hpp>
#include <mgtl/bit_array/bit_manipulator.hpp>

#pragma once
namespace mgtl {
using namespace mgtl::functional;
namespace bit_array {

  using _64_t = i_const_t<64>;
  using _32_t = i_const_t<32>;
  using _16_t = i_const_t<16>;
  using _8_t = i_const_t<8>;

  static constexpr auto _64 = i_const_v<64>;
  static constexpr auto _32 = i_const_v<32>;
  static constexpr auto _16 = i_const_v<16>;
  static constexpr auto _8 = i_const_v<8>;


  namespace bite_size {


    template<std::size_t N, typename _memory_t, class Enable = void> struct is_same_bite_size_t : public std::false_type
    {
    };

    template<std::size_t N, typename _memory_t>
    struct is_same_bite_size_t<N,
      _memory_t,
      typename std::enable_if_t<
        std::conjunction_v<is_integer_but_not_zero_t<std::size_t, N>, is_true<std::numeric_limits<_memory_t>::digits == N>>>>
      : public std::true_type
    {
    };

    template<std::size_t N, typename memory_t>
    static constexpr auto is_same_bite_size_v = is_same_bite_size_t<N, memory_t>::value;


    template<std::size_t N> static constexpr auto is_buildin_v = is_one_of_v<i_const_t<N>, _64_t, _32_t, _16_t, _8_t>;

    template<std::size_t N, class Enable = void> struct is_buildin_size_t : public std::false_type
    {
    };

    template<std::size_t N>
    struct is_buildin_size_t<N, typename std::enable_if_t<is_buildin_v<N>>> : public std::true_type
    {
    };

    template<std::size_t N> static constexpr auto is_buildin_size_v = is_buildin_size_t<N>::value;


    template<std::size_t N, typename _memory_t> struct bite_size_base
    {
      using memory_t = _memory_t;
      constexpr static auto memory_t_digits = std::numeric_limits<memory_t>::digits;
      constexpr static auto memory_size_whole_v = N / memory_t_digits;
      constexpr static auto number_of_bites_v = N;
    };
    template<std::size_t N, typename _memory_t, class IsMemortTSameSizeAsN = void> struct bite_size
    {
    };
    template<std::size_t N, typename _memory_t>
    struct bite_size<N, _memory_t, typename std::enable_if_t<!is_same_bite_size_v<N, _memory_t>>>
      : public bite_size_base<N, _memory_t>
    {
      using base = bite_size_base<N, _memory_t>;
      using base::memory_t_digits;
      using typename base::memory_t;
      using base::memory_size_whole_v;
      using base::number_of_bites_v;
    };


    template<std::size_t N, typename _memory_t>
    struct bite_size<N, _memory_t, typename std::enable_if_t<is_same_bite_size_v<N, _memory_t>>>
      : public bite_size_base<N, _memory_t>
    {
      using base = bite_size_base<N, _memory_t>;
      using base::memory_t_digits;
      using typename base::memory_t;
      using base::memory_size_whole_v;
      using base::number_of_bites_v;

      constexpr static auto memory_size_rest_v = N - (memory_t_digits * memory_size_whole_v);
      constexpr static auto memory_size_rounded_up_v = memory_size_whole_v + 1;
    };

  }// namespace bite_size

  namespace base {
    template<std::size_t N, typename memory_t> struct _BitArrayBase_t : public bite_size::bite_size<N, memory_t>
    {
      using bite_size_base = bite_size::bite_size<N, memory_t>;
      using BitManipulatorImpl = manipulator::BitManipulator<memory_t>;
      BitManipulatorImpl bm{};
      constexpr memory_t size()
      {
        return bite_size_base::base::number_of_bites_v;
      }
    };
  }// namespace base

  template<std::size_t N, typename memory_t = uint8_t>
  class _BitArrayBase_Array_t : public base::_BitArrayBase_t<N, memory_t>
  {

    constexpr auto fill() -> void
    {
      for (auto i = 0; i < this->_v.size(); i++) { _v[i] = memory_t{}; }
    }
  public:
    using base_1 = typename base::_BitArrayBase_t<N, memory_t>;
    using base_2 = typename base_1::bite_size_base;
    using base_1::size;
    using raw_memory_t = std::array<memory_t, base_2::memory_size_rounded_up_v>;


    template<std::size_t _N, typename _memory_t>
    friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_Array_t<_N, _memory_t> &);

    constexpr explicit _BitArrayBase_Array_t() { fill(); };
    alignas(memory_t) raw_memory_t _v;

    void set(memory_t bit)
    {
      constexpr auto index_max = base_2::memory_size_rounded_up_v - 1;
      const auto index = static_cast<memory_t>(bit / base_2::memory_t_digits);
      const auto element = (bit + base_2::memory_t_digits * index) % base_2::memory_t_digits;
      this->_v[index] = this->bm.set(element, std::move(this->_v));// MG Check if this is correct!
      //_v[index] = _v[index] | (static_cast<memory_t>(1) << element);
    }
  };

  template<std::size_t N, typename memory_t> class _BitArrayBase_SameSize_t : public base::_BitArrayBase_t<N, memory_t>
  {
  public:
    using base_1 = typename base::_BitArrayBase_t<N, memory_t>;
    using base_2 = typename base_1::bite_size_base;
    using base_1::size;
    using raw_memory_t = memory_t;

    template<std::size_t _N, typename _memory_t>
    friend std::ostream &operator<<(std::ostream &, const _BitArrayBase_SameSize_t<_N, _memory_t> &);
    alignas(raw_memory_t) raw_memory_t _v{};

    void set(memory_t bit) { this->_v = this->bm.set(bit, std::move(this->_v)); }
    void clear(memory_t bit) { this->_v = this->bm.clear(bit, std::move(this->_v)); }
    bool get(memory_t bit) { return this->bm.get(bit, std::move(this->_v)); }
  };


  namespace printer {

    template<std::size_t _N, typename _memory_t>
    std::ostream &operator<<(std::ostream &os, const _BitArrayBase_SameSize_t<_N, _memory_t> &L)
    {
      os << "[ " << L._v << " ]\n";

      return os;
    }
    template<std::size_t _N, typename _memory_t>
    std::ostream &operator<<(std::ostream &os, const _BitArrayBase_Array_t<_N, _memory_t> &L)
    {
      os << "[ ";
      for (auto it : L._v) { os << it << " "; }
      os << "]\n";
      return os;
    }

    struct PrintAsBytes
    {
      template<std::size_t _N, typename _memory_t>
      static std::string print(const _BitArrayBase_Array_t<_N, _memory_t> &l)
      {
        using bite_array_t = _BitArrayBase_Array_t<_N, _memory_t>;
        std::string s;

        size_t counter = 0;
        for (auto whole = 0; whole < bite_array_t::memory_size_whole_v; whole++) {
          for (auto digit = 0; digit < bite_array_t::memory_t_digits; digit++) {
            const auto _char = (((l._v[whole] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
            s += _char;
            counter++;
          }
        }

        for (auto rest = 0; rest < bite_array_t::memory_size_rest_v; rest++) {
          const auto _char =
            (((l._v[bite_array_t::memory_size_whole_v] >> counter) & static_cast<_memory_t>(1)) ? '1' : '0');
          s += _char;
          counter++;
        }
        return s;
      }

      template<std::size_t _N, typename _memory_t>
      static std::string print(const _BitArrayBase_SameSize_t<_N, _memory_t> &l)
      {
        std::string s;
        for (auto c = 0; c < _N; c++) {
          const auto _char = (((l._v >> c) & static_cast<_memory_t>(1)) ? '1' : '0');
          s += _char;
        }
        return s;
      }
    };
  }// namespace printer


  using BitArray64_t = _BitArrayBase_SameSize_t<_64, uint64_t>;
  using BitArray32_t = _BitArrayBase_SameSize_t<_32, uint32_t>;
  using BitArray16_t = _BitArrayBase_SameSize_t<_16, uint16_t>;
  using BitArray8_t = _BitArrayBase_SameSize_t<_8, uint8_t>;

  namespace conditional {
    template<std::size_t _N, std::size_t CompareN, typename TrueT, typename FalseT>
    using conditional_size_t = std::conditional_t<_N == CompareN, TrueT, FalseT>;

    template<std::size_t _N, typename T> using conditional_size8_t = conditional_size_t<_N, _8, BitArray8_t, T>;

    template<std::size_t _N, typename T>
    using conditional_size16_t = conditional_size_t<_N, _16, BitArray16_t, conditional_size8_t<_N, T>>;

    template<std::size_t _N, typename T>
    using conditional_size32_t = conditional_size_t<_N, _32, BitArray32_t, conditional_size16_t<_N, T>>;

    template<std::size_t _N, typename T>
    using conditional_size64_t = conditional_size_t<_N, _64, BitArray64_t, conditional_size32_t<_N, T>>;

    template<std::size_t _N> using self_configure_size_array_t = conditional_size64_t<_N, uint8_t>;

    template<std::size_t _N, typename T> using self_configure_size_memory_t_t = conditional_size64_t<_N, T>;

  }// namespace conditional
}// namespace bit_array

template<std::size_t _N, typename memory_t>
using BitArray = typename std::conditional_t<bit_array::bite_size::is_same_bite_size_v<_N, memory_t>,
  mgtl::bit_array::conditional::self_configure_size_memory_t_t<_N, memory_t>,
  bit_array::_BitArrayBase_Array_t<_N, memory_t>>;


template<std::size_t _N>
using BitArray_t = typename std::conditional_t<bit_array::bite_size::is_buildin_v<_N>,
  bit_array::conditional::self_configure_size_array_t<_N>,
  bit_array::_BitArrayBase_Array_t<_N>>;

}// namespace mgtl
