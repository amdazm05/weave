#ifndef _WEAVE_HTTP_CLIENT
#define _WEAVE_HTTP_CLITN

#include "weave/weave_engine.hpp"
#include <type_traits>

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
     *      Http = 80: The standard port number for the HTTP (Hypertext Transfer Protocol) is 80. 
     *              This is the default port used for unencrypted HTTP connections.
     *      Https= 443: 
     *              The standard port number for the HTTPS (Hypertext Transfer Protocol Secure) is 443. 
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
    using uri_t  = std::string_view;
    class UriHandle
    {
        private:
            uri_t       _uri;
        public:
            protocol_t  protocol;
            authority_t authority;
            path_t      path;
            query_t     query;
        public:
            UriHandle()=delete;
            //Parses URI aswell
            UriHandle(uri_t const uri);
            UriHandle(UriHandle &&) =default;
            UriHandle(UriHandle &)  =default;
            void update(uri_t const uri);
            ~UriHandle();
        private:
            void split();
    };

    class HttpClient
    {
        public:
            HttpClient(const WeaveEngine & engine_context);
            ~HttpClient();
        private:
            
    };
}


#endif //_WEAVE_HTTP_CLIENT
