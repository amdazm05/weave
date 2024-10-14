#ifndef _WEAVE_THREAD_POOL
#define _WEAVE_THREAD_POOL

#include <thread>
#include <functional>
#include <string_view>
#include <concepts>

namespace weave_utils
{
    template<size_t N>
    concept less_than_max_hardware_concurrency 
        = (N<std::thread::hardware_concurrency());

    template<typename thread_t=std::jthread, //thread type std::thread, std::jthread / custom threads
        size_t N=1,//number of threads
        typename func_t=std::function<void(std::string_view s)>>
    requires less_than_max_hardware_concurrency<N>
    class threadpool_t
    {
        private:
            std::vector<std::thread> pool_;
        public:
            threadpool_t()
            {   
                for(size_t i=0;i<N;i++)
                {
                    pool_.emplace_back([]()
                    {
                        
                    });
                }
            }
    };
}

//A thread pool needs to have an upper limit for the number of threads running
//A callback too if something is completed
    // needs some update



#endif //_WEAVE_THREAD_POOL