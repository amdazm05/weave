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
        std::suspend_always final_suspend() noexcept
        {
            return {};  
        }

        void unhandled_exception()
        {
            std::terminate();
        }
        static auto get_return_object_on_allocation_failure()
        {
            return Gen{nullptr}
        }
    };

    template <typename T>
    class generator{
        using promise_type = promise_t_base<T,generator>;
        using PromiseHandle = std::coroutine_handle<promise_type>;

        generator(generator const & ) = delete;
        generator(generator && rhs) : mcoroHandle(std::exchange(rhs.mcoroHandle,nullptr))
        {

        }

        ~generator()
        {
            if(mcoroHandle) mcoroHandle.destroy();
        }

        private:
            friend promise_type;
            explicit generator(promise_type * p):
                mcoroHandle{PromiseTypeHandle::from_promise(*p)}
            {}
            PromiseHandle mcoroHandle;
    };
}

#endif 