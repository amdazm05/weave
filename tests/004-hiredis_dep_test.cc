#include <catch2/catch_test_macros.hpp>
#include <hiredis/hiredis.h>
#include <iostream>
#include <memory>
#include <string>

// Must have redis-server running for this test to pass
// check systemctl
/******
 * systemctl status redis
 * ***** */ 


TEST_CASE("Redis Connection and Basic Commands", "[redis]")
{
    const char *hostname = "127.0.0.1";
    int port = 6379;
    std::cout << "Attempting to connect to Redis server at " << hostname << ":" << port << std::endl;
    auto c = std::unique_ptr<redisContext, decltype(&redisFree)>(redisConnect(hostname, port), redisFree);
    REQUIRE(c != nullptr);
    std::cout << c->errstr << std::endl;
    REQUIRE(c->err == 0);

    std::cout << "Connected to Redis server" << std::endl;
    auto reply = std::unique_ptr<redisReply, decltype(&freeReplyObject)>(
        static_cast<redisReply *>(redisCommand(c.get(), "SET mykey 123")), freeReplyObject);
    REQUIRE(reply != nullptr);
    std::cout<<reply->str<<std::endl;
    REQUIRE(reply->type == REDIS_REPLY_STATUS);
    REQUIRE(std::string(reply->str) == "OK");

    reply.reset(static_cast<redisReply *>(redisCommand(c.get(), "GET mykey")));
    REQUIRE(reply != nullptr);
    REQUIRE(reply->type == REDIS_REPLY_STRING);
    REQUIRE(std::string(reply->str) == "123");
}
