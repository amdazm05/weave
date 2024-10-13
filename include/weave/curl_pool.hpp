#ifndef _WEAVE_CURL_POOL
#define _WEAVE_CURL_POOL

#include <weave/curl_handler.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace weave_curl{
    class CurlPool{
        public:
            CurlPool(){
                handle_q_.push(new CurlHandler());
            }
            CurlPool(size_t N){
                while(N--){
                    handle_q_.push(new CurlHandler());
                }
            }

            CurlHandler * acquire(){
                std::unique_lock<std::mutex> lc(mtx_);
                while(handle_q_.empty())
                {
                    ctv_.wait(lc);
                }
                CurlHandler * handle = handle_q_.front();
                handle_q_.pop();
                return handle;
            }

            void release(CurlHandler* handle)
            {
                if(handle!=nullptr)
                {
                    std::lock_guard<std::mutex> lock(mtx_);
                    handle->reset();
                    handle_q_.push(handle);
                    ctv_.notify_one();
                }
            }

            ~CurlPool(){
                while(!handle_q_.empty()){
                    CurlHandler * dis= handle_q_.front();
                    handle_q_.pop();
                    dis->~CurlHandler();
                }
            }
        private:
            std::queue<CurlHandler *> handle_q_;
            std::mutex mtx_;
            std::condition_variable ctv_;
    };
}

#endif //_WEAVE_CURL_POOL