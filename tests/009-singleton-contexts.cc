#include <catch2/catch_test_macros.hpp>
#include <weave/weave_engine.hpp>

TEST_CASE("singleton-context-tests","")
{
    weave::WeaveEngine & eng = weave::WeaveEngine::init(1,2);
    REQUIRE(&weave::WeaveEngine::init(1,2)==&eng);
}