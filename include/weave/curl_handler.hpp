#ifndef _WEAVE_CURL_HANDLER_
#define _WEAVE_CURL_HANDLE

#include <curl/curl.h>
#include <memory>

class CurlHandler 
{
    private:
        CurlHandler();
        CurlHandler &operator=(CurlHandler const &) = delete;
        CurlHandler &operator=(CurlHandler &&) = delete;
        std::unique_ptr<CURL,decltype(&curl_easy_cleanup)>  _curl_handle; 
    public:
        static CurlHandler & instance();
        ~CurlHandler();
};

#endif //_WEAVE_CURL_HANDLE