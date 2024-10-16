#ifndef _WEAVE_THREAD_POOL
#define _WEAVE_THREAD_POOL

#include <thread>
#include <functional>
#include <string_view>
#include <concepts>
#include <mutex>
#include <condition_variable>
#include <queue>
namespace weave_utils
{
    //Use this mechanism for doing this
    //https://cmake.org/cmake/help/latest/module/ProcessorCount.html
    // template<size_t N>
    // concept less_than_max_hardware_concurrency 
    //     = (N<std::thread::hardware_concurrency());

    template<typename thread_t=std::jthread, //thread type std::thread, std::jthread / custom threads
        size_t N=1,//number of threads
        typename func_t=std::function<void(std::string_view s)>>
    // requires less_than_max_hardware_concurrency<N>
    class threadpool_t
    {
        private:
            std::vector<std::thread> pool_;
            std::mutex mtx_;
            std::queue<func_t> tasks_;
            std::condition_variable v_;
            bool stop_;
        public:
            threadpool_t()
            {   
                for(size_t i=0;i<N;i++)
                {
                    pool_.emplace_back([this]
                        ()
                    {
                        while (true)
                        {
                            func_t taskexe;
                            while(1)
                            {
                                std::unique_lock<std::mutex> l(mtx_);
                                v_.wait(l,[this](){
                                    return stop_ || !tasks_.empty();
                                });
                                if(stop_ && tasks_.empty())
                                    return;
                                taskexe = std::move(tasks_.front());
                                tasks_.pop();
                            }
                            //TODO find a mechanism to use arguments
                            taskexe("");
                        }
                    });
                }
            }
            
            void enqueue(func_t && func)
            {
                {
                    std::lock_guard<std::mutex> l(mtx_);
                    tasks_.emplace(func);
                }
                v_.notify_one();
            }

            ~threadpool_t()
            {
                {
                    std::lock_guard<std::mutex> l(mtx_);
                    stop_ = true;
                }
                v_.notify_all();
                // join the threads
                for(auto & thd:pool_)
                    thd.join();
            }
    };

    //WIP
    template<typename F, typename ...Args>
    auto submit_task(F && func, Args&&...arguments) -> decltype(func(arguments...))
    {
    std::function<decltype(func(arguments...))()> 
        funcwrapper = std::bind(std::forward<F>(func),std::forward<Args>(arguments)...);
    auto pack_func   = std::packaged_task<decltype(func(arguments...))()>(funcwrapper);
    pack_func();
    return pack_func.get_future().get();
    }

}

//A thread pool needs to have an upper limit for the number of threads running
//A callback too if something is completed
    // needs some update



#endif //_WEAVE_THREAD_POOL