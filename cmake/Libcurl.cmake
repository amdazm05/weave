macro(LibCurlFetchInstall LIBCURL_VERSION)
  set(LIBCURL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libcurl-src)
  set(LIBCURL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libcurl)
  set(LIBCURL_INCLUDE_DIR ${LIBCURL_INSTALL_DIR}/include)

  include(ExternalProject)
  ExternalProject_Add(
    Libcurl
    SOURCE_DIR ${LIBCURL_SOURCE_DIR}
    URL https://github.com/curl/curl/releases/download/curl-${LIBCURL_VERSION}/curl-8.8.0.tar.gz
    USES_TERMINAL_DOWNLOAD TRUE
    CONFIGURE_COMMAND ${LIBCURL_SOURCE_DIR}/configure
      --prefix=${LIBCURL_INSTALL_DIR}
      --enable-websockets
      --with-openssl=${OPENSSL_INSTALL_DIR}
    BUILD_COMMAND make
    TEST_COMMAND ""
    INSTALL_COMMAND make install
    INSTALL_DIR ${LIBCURL_INSTALL_DIR}
    UPDATE_COMMAND ""
    DOWNLOAD_EXTRACT_TIMESTAMP true
  )
  include_directories(${LIBCURL_INSTALL_DIR}/include)
endmacro(LibCurlFetchInstall)

function(LinkAndIncludeLibCurlToExecutable NAME_EXE)
  target_link_libraries(${NAME_EXE} PRIVATE ${LIBCURL_INSTALL_DIR}/lib/libcurl.a 
    ${OPENSSL_INSTALL_DIR}/lib/libssl.a 
    ${OPENSSL_INSTALL_DIR}/lib/libcrypto.a )
  target_include_directories(${NAME_EXE} PRIVATE ${LIBCURL_INSTALL_DIR}/include)
endfunction(LinkAndIncludeLibCurlToExecutable)
