#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>

TEST_CASE( "Presence of OpenSSL", "[single-file]" )
{
    SSL_library_init();
    SSL_load_error_strings();
    std::unique_ptr< SSL_CTX,decltype(&SSL_CTX_free)> ctx{SSL_CTX_new(TLS_client_method()),SSL_CTX_free};
    if (!ctx) 
    {
        REQUIRE(ctx!=nullptr);
        ctx.release();
    }
    std::unique_ptr< SSL,decltype(&SSL_free)> ss{SSL_new(ctx.get()),SSL_free};
    std::string_view version_str{SSL_get_version(ss.get())};
    std::cout<<version_str<<std::endl;
    REQUIRE(version_str.size());
}