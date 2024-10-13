#include <catch2/catch_test_macros.hpp>
#include <weave/curl_pool.hpp>
#include <thread>

using namespace weave_curl;
CurlPool pool(6);

void requester(std::string_view url)
{
    CurlHandler *handle{pool.acquire()};
    handle->set_url("http://www.google.com");
    REQUIRE(handle->perform_request().size()>0);
    pool.release(handle);
}

TEST_CASE("multiple-requests","curlpool-test")
{
    // spdlog::set_level(spdlog::level::trace);    
    std::vector<std::thread> tpool;
    for(int i =0;i<14;i++)
        tpool.push_back(std::thread(requester,""));

    for(auto & thd:tpool)
        thd.join();
}