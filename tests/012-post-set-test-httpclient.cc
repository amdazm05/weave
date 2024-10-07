#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>
#include <weave/weave_engine.hpp>

using namespace weave;

TEST_CASE("post-get-http-client","single-file")
{
    WeaveEngine & engine = WeaveEngine::get_context();
    std::array<std::string_view, 3> headers = {{
        "Content-Type: application/json",
        "Authorization: Bearer <TOKEN>",
        "User-Agent: weave"
    }};

    HttpClient httpclient(engine);
    std::cout<<"Set Headers"<<std::endl;
    httpclient.set_header(headers);
    std::cout<<httpclient.get("https://api.github.com/repos/amdazm05/weave/commits")<<std::endl;
}