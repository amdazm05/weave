#include <catch2/catch_test_macros.hpp>
#include <weave/curl_handler.hpp>
using namespace weave_curl;
TEST_CASE("curl-request-test","[single-file]")
{
    CurlHandler curlHandle; 
    spdlog::set_level(spdlog::level::trace);
    curlHandle.set_url("http://www.google.com");
    REQUIRE(curlHandle.perform_request().length()>0);
}