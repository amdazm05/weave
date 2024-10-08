#include <catch2/catch_test_macros.hpp>
#include <weave/weave_engine.hpp>

using namespace weave;

TEST_CASE("curl-set-header-tests","[single-file]")
{
    WeaveEngine & eng = WeaveEngine::get_context();
    CurlHandler & curlHandle = eng.get_curl_handle();  
    spdlog::set_level(spdlog::level::trace);
    curlHandle.set_url("http://localhost:3000");
    //Add Token here // Test fails
    curlHandle.set_post_fields(R"({"key": "value"})");
    curlHandle.set_headers({"Content-Type: application/json"});
    REQUIRE(curlHandle.perform_request().size()>0);
}