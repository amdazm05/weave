function(fetch_lib_curl LIBCURL_VERSION)
    # set(LIBCURL_VERSION "8.8.0")
    message("Downloading curl-${LIBCURL_VERSION}.tar.gz")
    set(LIBCURL_DOWNLOAD_URL "https://curl.se/download/curl-${LIBCURL_VERSION}.tar.gz")
    set(LIBCURL_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/libcurl-install")

    message(STATUS "Downloading libcurl VERSION ${LIBCURL_VERSION} from ${LIBCURL_DOWNLOAD_URL}...")
    file(DOWNLOAD ${LIBCURL_DOWNLOAD_URL} "${CMAKE_CURRENT_BINARY_DIR}/curl.tar.gz" SHOW_PROGRESS)
endfunction(fetch_lib_curl)