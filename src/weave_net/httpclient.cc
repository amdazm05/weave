#include <weave_net/httpclient.hpp>
using namespace weave;

HttpClient::HttpClient() 
{ 
    id_ = reinterpret_cast<uintptr_t >(this);
    spdlog::info("Initialised HTTPClient id: {}",id_);
}

HttpClient::~HttpClient()
{
    
}

void HttpClient::set_header(std::span<std::string_view> header_span)
{
    for(auto & header :header_span)
        curlhandle_.set_headers({header});
}

std::string_view HttpClient::get(std::string_view url)
{
    curlhandle_.set_url(url);    
    this->resbuffer_= curlhandle_.perform_request();
    return {resbuffer_};
}

void HttpClient::post(std::string_view url,std::string_view payload)
{
    curlhandle_.set_url(url);
    curlhandle_.set_post_fields(payload);
    curlhandle_.perform_request();
}