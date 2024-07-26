#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Presence of Catch2", "[single-file]" ) {
    REQUIRE( 1 == 1 );
}
