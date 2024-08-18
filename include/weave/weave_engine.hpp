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
            CurlHandler &curl_handle;
            WeaveEngine();
        public:
            [[noreturn]]static void init();
            static WeaveEngine &  get_context();
            WeaveEngine(WeaveEngine &&)=delete;
            WeaveEngine(const WeaveEngine &)=delete;
            void operator=(WeaveEngine const &)=delete;
            void operator=(WeaveEngine &&)=delete;
            ~WeaveEngine();
        private:
            bool is_init;
    };
}

#endif //_WEAVE_ENGINE