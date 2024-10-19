#ifndef _WEAVE_WEBSOCKET
#define _WEAVE_WEBSOCKET

#include <curl/curl.h>
#include <weave/curl/error_handler.hpp>
#include <memory>

using namespace weave_curl;
namespace weave
{
    // https://curl.se/docs/websocket.html
    class WebSocketClient
    {
        private:
            std::unique_ptr<CURL> handle_;
            std::string recv_buffer;
            CURLcode res;
            CurlErrorReporter err;
            std::string_view url_;
        public:
            WebSocketClient()=delete;
            WebSocketClient(std::string_view url);
            ~WebSocketClient();
            bool reconnect(std::string_view url);
            std::string && recv();
            void send(std::string_view payload);
    };
}

#endif //_WEAVE_WEBSOCKET