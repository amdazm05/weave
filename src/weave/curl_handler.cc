#include <weave/curl_handler.hpp>

CurlHandler::CurlHandler(): _curl_handle{curl_easy_init(),curl_easy_cleanup}
{
    if (!_curl_handle) {
        spdlog::error("Failed to initialize curl");
    }
}
CurlHandler & CurlHandler::instance()
{
    static CurlHandler _inst{};
    return _inst;
}

void CurlHandler::set_url(std::string_view url)
{
    CURLcode rc = curl_easy_setopt(_curl_handle.get(), CURLOPT_URL, url.data());
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
    res = curl_easy_setopt(_curl_handle.get(), CURLOPT_WRITEFUNCTION,
        weave_callbacks::WriteCallback);
    ErrorReporter.check_error(res);
    if(res!=CURLE_OK)
    {
        spdlog::error("curl_handler:request to url failed {}", curl_easy_strerror(res));
        return ""; // or handle the error as needed
    }
    res = curl_easy_setopt(_curl_handle.get(), CURLOPT_WRITEDATA, &response_buffer);
    ErrorReporter.check_error(res);
    res = curl_easy_perform(_curl_handle.get());
    ErrorReporter.check_error(res);
    spdlog::trace("curl_handler: response recivied {}",response_buffer);
    return response_buffer;
}

void CurlHandler::set_headers(const std::vector<std::string_view>&& headers)
{
    curl_slist * header_ptr =nullptr;
    for(const auto & header:headers)
    {
        curl_slist_append(header_ptr,header.data());    
        if(header_ptr) spdlog::info("Not null");
    }
    CURLcode res = curl_easy_setopt(_curl_handle.get(),CURLOPT_HTTPHEADER,header_ptr);
    ErrorReporter.check_error(res);
}

CurlHandler::~CurlHandler()
{
    /*stub*/
}