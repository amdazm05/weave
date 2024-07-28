#include <curl/curl.h>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

TEST_CASE("Presence of LibCurl", "[single-file]")
{
    std::string version_string{curl_version()};
    std::cout<<"libcurl version "<<version_string <<std::endl;
    REQUIRE(version_string.find("3.0.14")!=version_string.npos);
}