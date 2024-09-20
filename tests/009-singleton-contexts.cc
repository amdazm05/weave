#include <catch2/catch_test_macros.hpp>
#include <weave/weave_engine.hpp>

TEST_CASE("singleton-context-tests","")
{
    weave::WeaveEngine & eng = weave::WeaveEngine::get_context(); 
    CurlHandler & handle = eng.get_curl_handle();
    //this is the same handle as if I want to pass it around
    REQUIRE(&handle == &eng.get_curl_handle());
    REQUIRE(&weave::WeaveEngine::get_context()==&eng);
}