#ifndef _WEAVE_COMPILE_TIME
#define _WEAVE_COMPILE_TIME

#include <concepts>
#include <type_traits>
#include <ranges>
namespace weave_utils
{

    // Disabled
    // /************************************
    //  *  Boolean-Type Traits- operations-Concepts
    //  ************************************/
    // template <typename T, typename... V>
    // concept Is_same_as_any = (std::is_same_v<T, V> || ...);
    // /************************************
    //  *  Type-Traits-Concepts
    //  ************************************/
    // template <typename T>
    // concept get_underlying_type = std::remove_cvref<T>;

    // template <typename T>
    // concept Is_trivial = std::is_trivial<T>;

    // template <typename T>
    // concept Is_byte_type = Is_same_as_any<get_underlying_type<T>, std::byte, char, unsigned char>;

    // template <typename T>
    // concept Is_byte_container = (std::ranges::range<T> && Is_byte_type<std::ranges::range_t<T>>) || Is_byte_type<T>;
    
    template <typename T>
    concept IsIntegral = std::is_integral_v<T>;

    template <IsIntegral T>
    constexpr T constexpr_stoi(std::string_view sv)
    {
        if (sv.empty())
            return 0;

        T result = 0;
        bool is_negative = false;

        if (sv[0] == '-')
        {
            is_negative = true;
            sv.remove_prefix(1);
        }

        for (char c : sv)
        {
            if (c < '0' || c > '9')
                throw std::invalid_argument("Invalid integer format");
            result = result * 10 + (c - '0');
        }
        return is_negative ? -result : result;
    }

    template <std::string_view const &...Strs>
    struct join
    {
        static constexpr auto impl() noexcept
        {
            constexpr std::size_t len = (Strs.size() + ... + 0);
            std::array<char, len + 1> arr{};
            auto append = [i = 0, &arr](auto const &s) mutable
            {
                for (auto c : s)
                    arr[i++] = c;
            };
            (append(Strs), ...);
            return arr;
        }
        static constexpr auto arr = impl();
        static constexpr std::string_view value{arr.data(), arr.size() - 1};
    };
    template <std::string_view const&... Strs>
    static constexpr auto join_v = join<Strs...>::value;

    static constexpr size_t compute_string_sizes(std::string_view key, std::string_view value)
    {
        return key.length() + value.length();
    }

    template<size_t N>
    static constexpr size_t compute_string_len_in_array(
        const std::array<std::pair<std::string_view,std::string_view>,N> & arr)
    {
        size_t s =0;
        for(auto & [key,val]:arr)
            s+=compute_string_sizes(key,val);
        return s;
    }
    
}

#endif //_WEAVE_COMPILE_TIME