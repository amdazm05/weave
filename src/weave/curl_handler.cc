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
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string CurlHandler::perform_request()
{
    CURLcode res;
    std::string response_buffer;

    //call back to capture response
    res =curl_easy_setopt(_curl_handle.get(), CURLOPT_WRITEFUNCTION,WriteCallback);
    if(res!=CURLE_OK)
    {
        spdlog::error("curl_handler:request to url failed {}", curl_easy_strerror(res));
        return ""; // or handle the error as needed
    }
    res = curl_easy_setopt(_curl_handle.get(), CURLOPT_WRITEDATA, &response_buffer);
    if(res!=CURLE_OK)
    {
        spdlog::error("curl_handler:request to url failed {}", curl_easy_strerror(res));
        return ""; // or handle the error as needed
    }
    res = curl_easy_perform(_curl_handle.get());

    if (res != CURLE_OK) {
        spdlog::error("curl_handler:request to url failed {} {}", curl_easy_strerror(res),__LINE__);
        return ""; // or handle the error as needed
    }
    spdlog::trace("curl_handler: response recivied {}",response_buffer);
    return response_buffer;
}

CurlHandler::~CurlHandler()
{
    /*stub*/
}