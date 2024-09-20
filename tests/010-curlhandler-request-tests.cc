#include <catch2/catch_test_macros.hpp>
#include <weave/weave_engine.hpp>
using namespace weave;
TEST_CASE("curl-request-test","[single-file]")
{
    WeaveEngine & eng = WeaveEngine::get_context();
    CurlHandler & curlHandle = eng.get_curl_handle();  
    spdlog::set_level(spdlog::level::trace);
    curlHandle.set_url("http://www.google.com");
    REQUIRE(curlHandle.perform_request().length()>0);
}