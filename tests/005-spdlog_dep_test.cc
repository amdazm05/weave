#include <catch2/catch_test_macros.hpp>
#include <spdlog/spdlog.h>

TEST_CASE("Spdlog Connection and Basic Commands", "[spdlog]")
{
    spdlog::info("This is an info message");
    spdlog::error("This is an error message");
    REQUIRE(true);
}