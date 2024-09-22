#ifndef _WEAVE_CURL_ERROR_HANDLER
#define _WEAVE_CURL_ERROR_HANDLER

#include <curl/curl.h>
#include <string_view>
#include <source_location>
#include <spdlog/spdlog.h>
#include <exception>

namespace weave_curl
{
    class CurlErrorReporter
    {
        std::string_view error_;
        public:
            CurlErrorReporter();
            ~CurlErrorReporter();
            /// @brief gets us the last error
            /// @return 
            std::string_view operator()();
            void check_error(CURLcode &code,
                            const std::source_location &location = 
                             std::source_location::current());

            std::string_view get_last_error();
    };
}

#endif //_WEAVE_CURL_ERROR_HANDLER