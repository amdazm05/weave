#ifndef _WEAVE_COMPILE_TIME
#define _WEAVE_COMPILE_TIME

#include <concepts>
#include <type_traits>

namespace weave_utils
{

    /************************************
    *  Boolean-Type Traits- operations-Concepts
    ************************************/
    template <typename T, typename ...V>
    concept is_same_as_any = (std::is_same_as<T,V> || ...); 
    /************************************
     *  Type-Traits-Concepts
     ************************************/
    template<typename T>
    concept get_underlying_type = std::remove_cvref<T>;

    template<typename T>
    concept is_trivial = std::is_trivial<T>;

    template<typename T>
    concept is_byte_type = is_same_as_any<get_underlying_type<T>,std::byte,char, unsigned char>;

    template<typename T>
    concept is_byte_container = (std::ranges::range<T> && is_byte_type<std::ranges::range_t<T>>) || is_byte_type<T>;
}

#endif //_WEAVE_COMPILE_TIME