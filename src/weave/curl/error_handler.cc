#include <weave/curl/error_handler.hpp>
using namespace weave_curl;

CurlErrorReporter::CurlErrorReporter()
{

}

void CurlErrorReporter::check_error(CURLcode & code,
    const std::source_location& location = std::source_location::current())
{
    this->error_ = curl_easy_strerror(code);
    if(code!=CURLE_OK)
    {
        spdlog::error("{},{},{}",error_,
            location.function_name(),location.line());
    }
}

std::string_view CurlErrorReporter::operator()()
{
    return error_;
}