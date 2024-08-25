#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>

using namespace weave;

TEST_CASE("http-uri-protocol-test","[single-file]")
{
    constexpr UriHandleCT handle2{"https://www.testurl.com/"};
    REQUIRE( handle2.protocol==protocol_t::Https);
    REQUIRE( handle2.authority.host== "www.testurl.com");
    constexpr UriHandleCT handle3{"http://www.testurl.com/"};
    REQUIRE( handle3.protocol==protocol_t::Http);
    REQUIRE( handle3.authority.host=="www.testurl.com");
    constexpr UriHandleCT handle4
    	{"http://255.255.255:9000/path_to_something/home?param=value1,para=value2#"};
    REQUIRE( handle4.protocol==protocol_t::Http);
    REQUIRE( handle4.authority.host=="255.255.255");
    REQUIRE( handle4.authority.port=="9000");
    REQUIRE( handle4.path=="/path_to_something/home");
    REQUIRE( handle4.query=="param=value1,para=value2");
}
