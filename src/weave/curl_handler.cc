#include <weave/curl_handler.hpp>

CurlHandler::CurlHandler(): _curl_handle{curl_easy_init(),curl_easy_cleanup}
{
    
}
CurlHandler & CurlHandler::instance()
{
    static CurlHandler _inst{};
    return _inst;
}
CurlHandler::~CurlHandler()
{
    /*stub*/
}