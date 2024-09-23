#ifndef _WEAVE_CURL_HANDLER_
#define _WEAVE_CURL_HANDLE

#include <curl/curl.h>
#include <memory>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <weave/curl/callbacks.hpp>
#include <weave/curl/error_handler.hpp>
class CurlHandler 
{
    private:
        CurlHandler();
        CurlHandler &operator=(CurlHandler const &) = delete;
        CurlHandler &operator=(CurlHandler &&) = delete;
        std::unique_ptr<CURL,decltype(&curl_easy_cleanup)>  _curl_handle; 
        std::shared_ptr<CURLU> _url_handle;
        weave_curl::CurlErrorReporter ErrorReporter;
    public:
        void set_url(std::string_view url);
        void set_request_type(CURLoption requestType);
        void set_headers(const std::vector<std::string_view> && headers);
        void set_post_fields(std::string_view url);
        std::string perform_request();
        void set_timeout(size_t timeout);
        void set_user_agent(std::string_view url);
        void set_follow_redirects(bool enable);
        std::string get_last_error();
        
        /// @brief Gets you the only instance
        /// @return CurlHandle
        static CurlHandler & instance();
        ~CurlHandler();
};

#endif //_WEAVE_CURL_HANDLE