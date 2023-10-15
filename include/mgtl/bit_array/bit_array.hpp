#include <inttypes.h>

#include <array>
#include <cassert>
#include <iostream>
#include <limits>

template <typename memory_t>
struct BitManipulator {
    memory_t set(memory_t bit, memory_t _v)const { return static_cast<memory_t>((_v | (static_cast<memory_t>(1) << bit))); }
    memory_t toogle(memory_t bit, memory_t _v)const { return static_cast<memory_t>((_v | (static_cast<memory_t>(1) << bit))); }
    memory_t clear(memory_t bit, memory_t _v)const {

        return static_cast<memory_t>(_v & ~(static_cast<memory_t>(1) << bit));
    }

    memory_t check(memory_t bit, memory_t _v)const { return ((_v | (static_cast<memory_t>(1) << bit))); }
    bool get(memory_t bit, memory_t&& _v)const { return (_v>> bit) & static_cast<memory_t>(1);  }

};


using _zero = std::integral_constant<std::size_t, 0>;

static constexpr auto is_true_v = std::true_type::value;
static constexpr auto is_false_v = std::false_type::value;

template <typename T, typename U>
using is_not_same_t = std::negation<std::is_same<T, U>>;

template <typename T, typename U>
static constexpr auto is_not_same_v = is_not_same_t<T, U>::value;

template <std::size_t V, class Enable = void>
struct is_integer_but_not_zero_t : public std::false_type {};

template <std::size_t V>
struct is_integer_but_not_zero_t<
    V, typename std::enable_if_t<
           is_not_same_v<std::integral_constant<std::size_t, V>, _zero>>>
    : public std::true_type {};

template <std::size_t N>
static constexpr auto is_integer_but_not_zero_v =
    is_integer_but_not_zero_t<N>::value;

template <std::size_t NumberOfBites, typename _memory_t>
struct bite_size {
    using memory_t = _memory_t;
    constexpr static auto memory_t_digits =
        std::numeric_limits<memory_t>::digits;
    constexpr static auto memory_size_whole_v = NumberOfBites / memory_t_digits;
    constexpr static auto memory_size_rest_v =
        NumberOfBites - (memory_t_digits * memory_size_whole_v);
    constexpr static auto memory_size_rounded_up_v =
        memory_size_whole_v + (memory_size_rest_v > 0 ? 1 : 0);
    constexpr static auto number_of_bites_v = NumberOfBites;
    constexpr static bool same_bite_size_v =
        (memory_t_digits == number_of_bites_v);
};
template <typename _memory_t>
struct bite_size<0, _memory_t> {
    //static_assert(false, "Cannot use 0 bites.");
};

template <std::size_t NumberOfBites, typename _memory_t, class Enable = void>
struct is_same_bite_size_t : public std::false_type {};

template <typename _memory_t>
struct is_same_bite_size_t<0, _memory_t, void> : public std::false_type {
    //static_assert(false, "Cannot use 0 bites.");
};

template <std::size_t NumberOfBites, typename _memory_t>
struct is_same_bite_size_t<NumberOfBites, _memory_t,
                           typename std::enable_if_t<bite_size<
                               NumberOfBites, _memory_t>::same_bite_size_v>>
    : public std::true_type {};

template <std::size_t N, typename memory_t>
static constexpr auto is_same_bite_size_v =
    is_same_bite_size_t<N, memory_t>::value;

template <std::size_t N, typename memory_t>
struct BitArrayBase : public bite_size<N, memory_t> {
    using bite_size_base = bite_size<N, memory_t>;
    using BitManipulatorImpl = BitManipulator<memory_t>;
    BitManipulatorImpl bm{};
};

template <std::size_t N, typename memory_t>
class BitArrayBase_Array : public BitArrayBase<N, memory_t> {
    using base = typename BitArrayBase<N, memory_t>::bite_size_base;
    using raw_memory_t = std::array<memory_t, base::memory_size_rounded_up_v>;

    constexpr auto fill() -> void {
        for (auto i = 0; i < this->_v.size(); i++) {
            _v[i] = memory_t{};
        }
    }

   public:
    template <std::size_t _N, typename _memory_t>
    friend std::ostream& operator<<(std::ostream&,
                                    const BitArrayBase_Array<_N, _memory_t>&);

    constexpr explicit BitArrayBase_Array() { fill(); };
    alignas(memory_t) raw_memory_t _v;

    void set(memory_t bit) {
        constexpr auto index_max = base::memory_size_rounded_up_v - 1;
        const auto index = static_cast<memory_t>(bit / base::memory_t_digits);
        const auto element =
            (bit + base::memory_t_digits * index) % base::memory_t_digits;
            this->_v[index] = this->bm.set(element, std::move(this->_v)); //MG Check if this is correct!
        //_v[index] = _v[index] | (static_cast<memory_t>(1) << element);
    }
};

template <std::size_t N, typename memory_t>
class BitArrayBase_SameSize : public BitArrayBase<N, memory_t> {
    using base = typename BitArrayBase<N, memory_t>::bite_size_base;
    using raw_memory_t = memory_t;
   public:
    template <std::size_t _N, typename _memory_t>
    friend std::ostream& operator<<(
        std::ostream&, const BitArrayBase_SameSize<_N, _memory_t>&);
    alignas(raw_memory_t) raw_memory_t _v{};

        void set(memory_t bit) { this->_v = this->bm.set(bit, std::move(this->_v)); }
        void clear(memory_t bit) { this->_v = this->bm.clear(bit, std::move(this->_v)); }
        bool get(memory_t bit) { return this->bm.get(bit, std::move(this->_v)); }

};

template <std::size_t _N, typename _memory_t>
std::ostream& operator<<(std::ostream& os,
                         const BitArrayBase_SameSize<_N, _memory_t>& L) {
    os << "[ " << L._v << " ]\n";

    return os;
}
template <std::size_t _N, typename _memory_t>
std::ostream& operator<<(std::ostream& os,
                         const BitArrayBase_Array<_N, _memory_t>& L) {
    os << "[ ";
    for (auto it : L._v) {
        os << it << " ";
    }
    os << "]\n";
    return os;
}

struct PrintAsBytes {
    template <std::size_t _N, typename _memory_t>
    static std::string print(const BitArrayBase_Array<_N, _memory_t>& l) {
        using bite_array_t = BitArrayBase_Array<_N, _memory_t>;
        std::string s;

        size_t counter = 0;
        for (auto whole = 0; whole < bite_array_t::memory_size_whole_v;
             whole++) {
            for (auto digit = 0; digit < bite_array_t::memory_t_digits;
                 digit++) {
                const auto _char =
                    (l._v[whole] >> counter) & static_cast<_memory_t>(1) ? '1' : '0';
                s += _char;
                counter++;
            }
        }

        for (auto rest = 0; rest < bite_array_t::memory_size_rest_v; rest++) {
            const auto _char =
                (l._v[bite_array_t::memory_size_whole_v] >> counter) &
                        static_cast<_memory_t>(1)
                    ? '1'
                    : '0';
            s += _char;
            counter++;
        }
        return s;
    }

    template <std::size_t _N, typename _memory_t>
    static std::string print(const BitArrayBase_SameSize<_N, _memory_t>& l) {
        std::string s;
        for (auto c = 0; c < _N; c++) {
            const auto _char = (l._v >> c) & static_cast<_memory_t>(1) ? '1' : '0';
            s += _char;
        }
        return s;
    }
};

using BitArray64 = BitArrayBase_SameSize<64,uint64_t>;
using BitArray32= BitArrayBase_SameSize<32,uint32_t>;
using BitArray16 = BitArrayBase_SameSize<16, uint16_t>;
using BitArray8 = BitArrayBase_SameSize<8,uint8_t>;


template <std::size_t _N,std::size_t CompareN,  typename T , typename NotT >
using  conditional_size_t = std::conditional_t<_N == CompareN, T, NotT>;

template <std::size_t _N, typename T>
using  conditional_size8_t = conditional_size_t<_N,8, BitArray8,T>;

template <std::size_t _N, typename T>
using  conditional_size16_t = conditional_size_t<_N,16, BitArray16,conditional_size8_t<_N,T>>;

template <std::size_t _N, typename T>
using  conditional_size32_t = conditional_size_t<_N,32, BitArray32,conditional_size16_t<_N,T>>;

template <std::size_t _N, typename T>
using  conditional_size64_t = conditional_size_t<_N,64, BitArray64,conditional_size32_t<_N,T>>;

template <std::size_t _N, typename memory_t>
using BitArray =
    typename std::conditional_t<is_same_bite_size_v<_N, memory_t>,
                                /*True*///BitArrayBase_SameSize<_N, memory_t>,
                                    conditional_size64_t<_N,memory_t>,
                                /*False*/BitArrayBase_Array<_N, memory_t>>;

/*
Should not compile!
*/

/*
int main() {
    std::cout << BitArray<127, uint64_t>::memory_t_digits
              << "memory_t_digits \n";
    std::cout << BitArray<127, uint64_t>::memory_size_whole_v
              << "memory_size_whole_v \n";
    std::cout << BitArray<127, uint64_t>::memory_size_rest_v
              << "memory_size_rest_v \n";
    std::cout << BitArray<127, uint64_t>::memory_size_rounded_up_v
              << "memory_size_rounded_up_v \n";

    BitArray<128, uint64_t> t;
    std::cout << t << " BitArray<128, uint64_t> \n";

    BitArray<64, uint64_t> t2;
    std::cout << t2 << "  BitArray<64, uint64_t> t2\n";

    BitArray<67, uint64_t> t3;
    std::cout << t3 << " BitArray<241, uint64_t> t3\n";
    // MenosGrandes remove second parameter. It should be deducted based on the
    // first value
    std::cout << PrintAsBytes::print(t) << " -\n";
    std::cout << PrintAsBytes::print(t2) << " -\n";
    std::cout << PrintAsBytes::print(t3) << " -\n";

    {
        t2.set(0);
        assert(t2._v == 1);
        t2.set(1);
        assert(t2._v == 3);
    }
}
*/
