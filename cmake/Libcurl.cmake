function(LibCurlFetchInstall VERSION)
    if(LIBCURL_FOUND)
        message("LIBCURL_FOUND - Skipping")
        return()
    endif()
    set(TEMP ${CMAKE_MODULE_PATH})
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/libcurl)
    include(fetch_lib_curl)
    include(extract_lib_curl)
    set(LIBCURL_INSTALL_DIR ${CMAKE_BINARY_DIR}/libcurl)

    fetch_lib_curl(${VERSION})
    extract_libcurl()
    # Configure libcurl
    execute_process(
        COMMAND ./configure --with-openssl --prefix=${LIBCURL_INSTALL_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/curl-${VERSION}
    )

    # Build libcurl
    execute_process(
        COMMAND make -j4
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/curl-${VERSION}
    )

    # Install libcurl
    execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/curl-${VERSION}
    )
    set(CMAKE_MODULE_PATH ${TEMP})
endfunction(LibCurlFetchInstall VERSION)
