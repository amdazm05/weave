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
}

#endif //_WEAVE_COMPILE_TIME