#ifndef _WEAVE_HTTP_CLIENT
#define _WEAVE_HTTP_CLITN

#include "weave/weave_engine.hpp"
#include "weave_ds/const_expr_map.tpp"
#include <type_traits>
#include <unordered_map>
#include <algorithm>

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

    static constexpr std::array<std::pair<std::string_view, protocol_t>, 3>
        protocol_map = {{{"http", protocol_t::Http},
                         {"https", protocol_t::Https}}};
    struct authority_t
    {
        std::string_view user;
        std::string_view host;
        std::string_view port;
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
    static constexpr protocol_t get_protocol_from_view(
           const std::string_view prot)
    {
        constexpr auto map_prot = ct_map<std::string_view, protocol_t, protocol_map.size()>
            {{protocol_map}};
        return map_prot.find(prot);
    }
    
    class UriHandleCT
    {
    public:
        using uri_t = std::string_view;
        using path_t = std::string_view;
        using query_t = std::string_view;

    public:
        constexpr UriHandleCT(uri_t uri) : _uri(uri)
        {
            split(_uri, protocol, authority, path,query);
        }

        constexpr UriHandleCT(UriHandleCT &&) = default;
        constexpr UriHandleCT(UriHandleCT &) = default;

        constexpr void update(uri_t uri)
        {
            _uri = uri;
            split(_uri, protocol, authority, path,query);
        }
        ~UriHandleCT() = default;

    private:
        static constexpr void split(
            uri_t uri, protocol_t &protocol, authority_t &authority,
            path_t &path, query_t &query)
        {
            if (uri == "")
                return;
            auto protocol_str = uri.substr(0, uri.find(":"));
            if (protocol_str == "")
                return;
            protocol = get_protocol_from_view(protocol_str);
            auto offset_to_auth = uri.find(":")+3; //skips // here
            //This may not be a case
            //if we have a .com then find it next : here
            auto check_type_hostname = uri.find(":",uri.find(":")+3);
            auto index_hostname
		        =   check_type_hostname==uri.npos?
                    uri.find(".com")+4:check_type_hostname;
            auto auth_str = uri.substr(offset_to_auth,index_hostname-offset_to_auth);
            authority.host = auth_str;
            if(check_type_hostname!=uri.npos)
                authority.port = uri.substr(index_hostname+1,
				uri.find("/",index_hostname)-index_hostname-1);
	    else 
		authority.port = "";
	    auto port_end_index = uri.find("/",index_hostname);	    
	    path = uri.substr(port_end_index,
			    uri.find("?")-port_end_index);
	    auto query_start_index = uri.find("?");
            if(query_start_index!=uri.npos)
	        query = uri.substr(query_start_index+1,
           		    uri.find("#")-query_start_index-1);
	    else 
		query = "";
	}
    private:
        uri_t _uri;
    public:
        protocol_t protocol;
        authority_t authority;
        path_t path;
    	query_t query;
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
//https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3420.html
