#include <weave_net/websocket.hpp>
using namespace weave;

WebSocketClient::WebSocketClient(std::string_view url)
    : handle_(curl_easy_init(), curl_easy_cleanup), url_(url)
{

}
WebSocketClient::~WebSocketClient()
{

}
static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t totalSize = size * nmemb;
    std::string message(static_cast<char *>(contents), totalSize);
    return totalSize;
}
bool WebSocketClient::reconnect(std::string_view url)
{
    return {};
}

bool WebSocketClient::connect()
{
    if(!handle_){
        spdlog::error("WebSocket handle invalid");
        return false;
    }

    curl_easy_setopt(handle_.get(), CURLOPT_URL, url_.data());
    curl_easy_setopt(handle_.get(), CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(handle_.get(), CURLOPT_WRITEDATA, this);
    curl_easy_setopt(handle_.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
    
    res = curl_easy_perform(handle_.get());
    err.check_error(res);
    return true;
}

std::string &&WebSocketClient::recv()
{
    return {};
}
void WebSocketClient::send(std::string_view payload)
{

}
