#include <weave/curl/error_handler.hpp>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <curl/curl.h>

namespace weave_curl
{

    CurlErrorReporter::CurlErrorReporter()
    {
    }

    CurlErrorReporter::~CurlErrorReporter() 
    {
        
    }

    void CurlErrorReporter::check_error(CURLcode &code,
                                        const std::source_location &location) // No default value here
    {
        this->error_ = curl_easy_strerror(code);
        if (code != CURLE_OK)
        {
            spdlog::error("{},{},{}", error_,
                          location.function_name(), location.line());
            throw std::runtime_error("CurlReporter: Exception thrown");
        }
    }

    std::string_view CurlErrorReporter::operator()()
    {
        return error_;
    }

    std::string_view CurlErrorReporter::get_last_error()
    {
        return error_; // Ensure this method is defined
    }

}