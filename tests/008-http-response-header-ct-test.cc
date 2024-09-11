#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>

using namespace weave;

TEST_CASE("http-response-header-tests","[single-file]")
{
  constexpr std::array<std::pair<std::string_view , std::string_view>, 2> headers = {{
        {"Content-Type", "text/plain"},
        {"Cache-Control", "no-cache"}
    }};
  static constexpr  char okMessage[] = "OK";
  static constexpr  char okStatus[] = "200"; 
  ResponseCT<okMessage,okStatus,headers.size()> ct(headers);
  //Expected output
  std::string_view s = "HTTP/1.1 200 OK \nContent-Type:text/plain \nCache-Control:no-cache \n";
  REQUIRE(ct.to_string()==s);
}


