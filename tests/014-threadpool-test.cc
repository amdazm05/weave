#include <catch2/catch_test_macros.hpp>
#include <weave_utils/threadpool.hpp>
#include <thread>

TEST_CASE("thread-pool-test","thread-pool")
{
    weave_utils::threadpool_t<std::jthread,3> tp;
}