#include <weave/curl_handler.hpp>
using namespace weave_curl;
CurlHandler::CurlHandler()
{
    _curl_handle = curl_easy_init();
    if (!_curl_handle) {
        spdlog::error("Failed to initialize curl");
    }
}

std::shared_ptr<CurlHandler> CurlHandler::get_context()
{
    return shared_from_this();
}

void CurlHandler::reset()
{
    curl_easy_reset(_curl_handle);
}

void CurlHandler::set_url(std::string_view url)
{
    if(!_curl_handle)
    {
        return;
    }
    CURLcode rc = curl_easy_setopt(_curl_handle, CURLOPT_URL, url.data());
    if(rc!=CURLE_OK)
    {
        spdlog::error("curl_handler:set url failed");
        return;
    }
    spdlog::info("curl_handler: url set {}",url);
}

std::string CurlHandler::perform_request()
{
    CURLcode res;
    std::string response_buffer;

    //call back to capture response
    res = curl_easy_setopt(_curl_handle, CURLOPT_WRITEFUNCTION,
        weave_callbacks::WriteCallback);
    ErrorReporter.check_error(res);
    res = curl_easy_setopt(_curl_handle, CURLOPT_WRITEDATA, &response_buffer);
    ErrorReporter.check_error(res);
    if(_curl_handle)
    {
        res = curl_easy_perform(_curl_handle);
        ErrorReporter.check_error(res);
    }
    spdlog::trace("curl_handler: response recivied {}",response_buffer);
    return response_buffer;
}

void CurlHandler::set_post_fields(std::string_view url)
{
    CURLcode res;
    res=curl_easy_setopt(_curl_handle, CURLOPT_POSTFIELDS, url.data());
    ErrorReporter.check_error(res);
}

void CurlHandler::set_headers(const std::vector<std::string_view>&& headers)
{
    curl_slist * header_ptr =nullptr;
    for(const auto & header:headers)
    {
        header_ptr = curl_slist_append(header_ptr,header.data());    
    }
    CURLcode res = curl_easy_setopt(_curl_handle,CURLOPT_HTTPHEADER,header_ptr);
    ErrorReporter.check_error(res);
}

void CurlHandler::set_timeout(size_t timeout)
{
    CURLcode res = curl_easy_setopt(_curl_handle,CURLOPT_TIMEOUT_MS,timeout);
    ErrorReporter.check_error(res);
}

void CurlHandler::set_user_agent(std::string_view agent)
{
    CURLcode res = curl_easy_setopt(_curl_handle,CURLOPT_USERAGENT,agent);
    ErrorReporter.check_error(res);
}

CurlHandler::~CurlHandler()
{
    /*stub*/
    curl_easy_cleanup(_curl_handle);
}