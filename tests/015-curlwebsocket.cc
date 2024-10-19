#include <catch2/catch_test_macros.hpp>
#include <weave_net/websocket.hpp>

//It is still experimental in libcurl //but anyhow this was just for analysis
TEST_CASE("curl-websocket","curl-websocket-tests")
{
    weave::WebSocketClient socket("ws://localhost:8765");
    socket.connect();
}