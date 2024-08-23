#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>

using namespace weave;

TEST_CASE("http-uri-protocol-test","[single-file]")
{
    constexpr UriHandleCT handle{"www.testurl.com"};
    REQUIRE( handle.protocol==protocol_t::Unknown);
    constexpr UriHandleCT handle2{"https://www.testurl.com"};
    REQUIRE( handle2.protocol==protocol_t::Https);
    constexpr UriHandleCT handle3{"http://www.testurl.com"};
    REQUIRE( handle3.protocol==protocol_t::Http);
}