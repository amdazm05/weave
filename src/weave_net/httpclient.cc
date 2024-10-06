#include <weave_net/httpclient.hpp>
using namespace weave;

HttpClient::HttpClient(WeaveEngine & engine) : engine_(engine)
{ 
    id_ = reinterpret_cast<uint32_t>(this);
    spdlog::info("Initialised HTTPClient id: {}",id_);
}

void HttpClient::set_header(std::span<std::string_view> header_span)
{
    CurlHandler & curlhandle = engine_.get_curl_handle();
    for(auto & header :header_span)
        curlhandle.set_headers({header});
}

std::string_view HttpClient::get(std::string_view url)
{
    CurlHandler & curlhandle = engine_.get_curl_handle();
    curlhandle.set_url(url);    
    this->resbuffer_= curlhandle.perform_request();
    return {resbuffer_};
}