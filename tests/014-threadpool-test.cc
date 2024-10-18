#include <catch2/catch_test_macros.hpp>
#include <weave_utils/threadpool.hpp>
#include <thread>
#include <iostream>

std::string_view something(std::string_view i)
{
    sleep(1);
    return i;
}

TEST_CASE("thread-pool-test","thread-pool")
{
    weave_utils::threadpool_t<std::jthread,3> tp;
    std::cout<<tp.submit_task(something,"hi");
    std::cout<<tp.submit_task(something,"hello");
    REQUIRE(true);
}