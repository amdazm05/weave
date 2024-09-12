#include <catch2/catch_test_macros.hpp>
#include <weave_net/httpclient.hpp>
#include <weave_utils/compile_time.tpp>

using namespace weave;

TEST_CASE("http-response-request-header-tests","[single-file]")
{
  constexpr weave::weave_ct_headers<2> headers{{
        {"Content-Type", "text/plain"},
        {"Cache-Control", "no-cache"}
    }};
  //Example of Response
  HttpProtocolEntityCompileTime<headers.size(),HTTPEntityType::RESPONSE,
    weave_utils::compute_string_len_in_array(headers)> ct{headers,"200","OK"};
  std::string_view s = "HTTP/1.1 200 OK\nContent-Type:text/plain\nCache-Control:no-cache\n";
  REQUIRE(ct.to_string()==s);

  HttpProtocolEntityCompileTime<headers.size(),HTTPEntityType::REQUEST,
    weave_utils::compute_string_len_in_array(headers)> ct_req{headers,"200","OK"};
  std::string_view sreq = "200 OK HTTP/1.1\nContent-Type:text/plain\nCache-Control:no-cache\n";
  REQUIRE(ct_req.to_string()==sreq);
}
