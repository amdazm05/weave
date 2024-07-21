function(LibCurlFetchInstall LIBCURL_VERSION)
    include(FetchContent)
    FetchContent_Declare(libcurl 
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG "curl-${LIBCURL_VERSION}")
    FetchContent_GetProperties(libcurl)
    FetchContent_MakeAvailable(libcurl)
endfunction(LibCurlFetchInstall)
