#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>

using namespace weave;

TEST_CASE("http-response-header-tests","[single-file]")
{
  constexpr std::array<std::pair<std::string_view, std::string_view>, 2> headers = {{
        {"Content-Type", "text/plain"},
        {"Cache-Control", "no-cache"}
    }};
  static constexpr  char okMessage[] = "OK";
  static constexpr  char okStatus[] = "200"; 
  ResponseCT<okMessage,okStatus,2> ct{headers,"Hello"};

  static constexpr  char errorMessage[] = "ERROR";
  static constexpr  char errStatus[] = "404"; 
  ResponseCT<errorMessage,errStatus,2> ct2{headers,"Something"};
  std::cout<<ct.to_string()<<std::endl;
  std::cout<<ct2.to_string()<<std::endl;
}


