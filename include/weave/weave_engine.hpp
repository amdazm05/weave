#ifndef _WEAVE_ENGINE
#define _WEAVE_ENGINE

#include <memory>
#include <iostream>

#include <curl/curl.h>
#include <hiredis/hiredis.h>
#include <openssl/ssl.h>
#include <weave/curl/error_handler.hpp>
#include <weave/curl_pool.hpp>

namespace weave
{
    /***************************************************************************
     * Weave Engine Initialises a libraries and disposes any contexts remaining
     ***************************************************************************/
    class WeaveEngine
    {
        private:
            weave_curl::CurlPool curl_pool_;
            WeaveEngine();
            weave_curl::CurlErrorReporter curl_error_reporter;
        public:
            static WeaveEngine &  init(size_t curlpool_size,size_t threadpool);
            WeaveEngine(WeaveEngine &&)=delete;
            WeaveEngine(const WeaveEngine &)=delete;
            void operator=(WeaveEngine const &)=delete;
            void operator=(WeaveEngine &&)=delete;
            ~WeaveEngine();
        private:
            static WeaveEngine * inst;
    };
}

#endif //_WEAVE_ENGINE