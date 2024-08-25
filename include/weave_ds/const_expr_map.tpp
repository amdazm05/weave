#ifndef _WEAVE_CONSTEXPR_MAP
#define _WEAVE_CONSTEXPR_MAP
#include <array>
#include <algorithm>

template <typename Key, typename Value, std::size_t  Size>
struct ct_map
{
    std::array<std::pair<Key, Value>, Size> _data;
    [[nodiscard]] constexpr Value find(const Key &key) const
    {
        const auto it =
            std::find_if(_data.begin(), _data.end(),
                         [&key](const std::pair<Key, Value> &pr)
                         {
                             return key == pr.first;
                         });
        if (it!=_data.end())
            return (*it).second;
        else
            throw std::range_error("Not Found");
    }
};

#endif //_WEAVE_CONSTEXPR_MAP