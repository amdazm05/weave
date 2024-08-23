#ifndef _WEAVE_HTTP_CLIENT
#define _WEAVE_HTTP_CLITN

#include "weave/weave_engine.hpp"
#include <type_traits>
#include <unordered_map>

namespace weave
{
    /****
     *      Components Required  for HTTP component
     *      URI handling
     *      Connection Handler
     *      Request Handler
     *      Response Handler
     *      Error Handling
     ***/

    using port_t = int;
    /****
     *      Http = 80: The standard port number for the HTTP
     *               (Hypertext Transfer Protocol) is 80.
     *               This is the default port used for unencrypted HTTP connections.
     *      Https= 443:
     *              The standard port number for the HTTPS
     *              (Hypertext Transfer Protocol Secure) is 443.
     *              This is the default port used for encrypted HTTP connections over SSL/TLS.
     *      Unknown= -1:
     *              The Unknown value is assigned a value of -1 to represent a protocol that is not recognized
     *              or does not have a standard port number associated with it.
     ***/
    enum class protocol_t : port_t
    {
        Http = 80,
        Https = 443,
        Unknown = -1,
    };
    const std::unordered_map<std::string_view, protocol_t> map{{{"http", protocol_t::Http},
                                                                {"https", protocol_t::Https}}};
    struct authority_t
    {
        std::string_view user;
        std::string_view host;
        port_t port;
    };
    using path_t = std::string_view;
    using query_t = std::string_view;
    /****
     *      Handles URIs to extract information
     *      uri_t what components does it have.
     *      Scheme :  "http", "https", "ftp", "file", "mailto"
     *      Authority :  (e.g., "user:password@")
     *               User information: "username:password"
     *               Host: "www.example.com"
     *               Port: 8080
     *      Path : ("/")
     *      Query : ("?")
     *      Fragment :  "#"
     ***/
    using uri_t = std::string_view;
    class UriHandleCT
    {
    public:
        using uri_t = std::string_view;
        // using protocol_t = std::string_view;
        using authority_t = std::string_view;
        using path_t = std::string_view;
        using query_t = std::string_view;

    public:
        constexpr UriHandleCT(uri_t uri) : _uri(uri)
        {
            split(_uri, protocol, authority, path);
        }

        constexpr UriHandleCT(UriHandleCT &&) = default;
        constexpr UriHandleCT(UriHandleCT &) = default;

        constexpr void update(uri_t uri)
        {
            _uri = uri;
            split(_uri, protocol, authority, path);
        }
        ~UriHandleCT() = default;

    private:
        static constexpr void split(
            uri_t uri, protocol_t &protocol, authority_t authority,
            path_t path)
        {
            if (uri == "")
                return;
            auto protocol_str = uri.substr(0, uri.find(":"));
            if (protocol_str == "")
                return;
            protocol = get_protocol_from_view(protocol_str);
        }
        static constexpr protocol_t
        get_protocol_from_view(std::string_view prot)
        {
            if(prot=="http") return protocol_t::Http;
            if(prot=="https") return protocol_t::Https;
            return protocol_t::Unknown;
        }
    private:
        uri_t _uri;
    public:
        protocol_t protocol;
        authority_t authority;
        path_t path;
    };

    class HttpClient
    {
    public:
        HttpClient(const WeaveEngine &engine_context);
        ~HttpClient();

    private:
    };
}

#endif //_WEAVE_HTTP_CLIENT
