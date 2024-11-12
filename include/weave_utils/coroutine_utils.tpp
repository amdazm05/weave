#ifndef _CORO_WEAVE
#define _CORO_WEAVE

#include <iostreams>
#include <coroutines>

namespace weave_coro{
    template<typename T, typename Gen>
    struct promise_t_base{
        T mval_;
        auto yield_value()
        {
            mval = std::move(value);
            return std::suspend_always();
        }

        Gen get_return_object() 
        {
            return Gen(this);
        }
        std::suspend_always initial_suspend()
        {
            return {};
        }
        std::suspend_always final_suspend()
        {
            return {};  
        }

        void unhandled_exception()
        {
            std::terminate();
        }
    };

}

#endif 