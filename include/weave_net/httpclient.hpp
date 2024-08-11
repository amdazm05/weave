#ifndef _WEAVE_HTTP_CLIENT
#define _WEAVE_HTTP_CLITN

#include "weave/weave_engine.hpp"
#include <type
namespace weave
{
    using port_t = int;
    /****
     *   Http = 80: The standard port number for the HTTP (Hypertext Transfer Protocol) is 80. 
     *              This is the default port used for unencrypted HTTP connections.
     *   Https= 443: 
     *              The standard port number for the HTTPS (Hypertext Transfer Protocol Secure) is 443. 
     *              This is the default port used for encrypted HTTP connections over SSL/TLS.
     *   Unknown= -1: 
     *              The Unknown value is assigned a value of -1 to represent a protocol that is not recognized 
     *              or does not have a standard port number associated with it.
     */
    enum class protocol_type : port_t 
    {
        Http = 80,
        Https = 443,
        Unknown = -1,
    };
    
    class WeaveHTTPClient
    {
        public:
            WeaveHTTPClient(const WeaveEngine & engine_context);
            ~WeaveHTTPClient();
        private:
            
    };
}


#endif //_WEAVE_HTTP_CLIENT
