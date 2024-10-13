#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>
#include <weave/weave_engine.hpp>
#include <spdlog/spdlog.h>

using namespace weave;

TEST_CASE("post-get-http-client","single-file")
{
    std::array<std::string_view, 3> headers = {{
        "Content-Type: application/json",
        "Authorization: Bearer <TOKEN>",
        "User-Agent: weave"
    }};
    spdlog::set_level(spdlog::level::trace);
    HttpClient httpclient;
    httpclient.set_header(headers);
    REQUIRE(httpclient.get("https://api.github.com/repos/amdazm05/weave/commits").size()>1);
    
    std::array<std::string_view,1> headersp = {{"Content-Type: application/json"}};
    std::string_view headerpost ={{ R"({"key": "value"})"}};
    httpclient.set_header(headersp);
    httpclient.post("http://localhost:3000",headerpost);

}