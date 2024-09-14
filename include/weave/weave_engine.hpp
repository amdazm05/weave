#ifndef _WEAVE_ENGINE
#define _WEAVE_ENGINE

#include <memory>
#include <iostream>

#include <curl/curl.h>
#include <hiredis/hiredis.h>
#include <openssl/ssl.h>
#include "curl_handler.hpp"

namespace weave
{
    /***************************************************************************
     * Weave Engine Initialises a libraries and disposes any contexts remaining
     ***************************************************************************/
    class WeaveEngine
    {
        private:
            CurlHandler& _curlHandler;
        private:
            WeaveEngine();
        public:
            static WeaveEngine &  get_context();
            WeaveEngine(WeaveEngine &&)=delete;
            WeaveEngine(const WeaveEngine &)=delete;
            void operator=(WeaveEngine const &)=delete;
            void operator=(WeaveEngine &&)=delete;
            CurlHandler & get_curl_handle();
            ~WeaveEngine();
        private:
            static WeaveEngine * inst;
    };
}

#endif //_WEAVE_ENGINE