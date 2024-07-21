function(LibOpenSSL OPENSSL_VERSION)
    set(OPENSSL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl-src) # default path by CMake
    set(OPENSSL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl)
    set(OPENSSL_INCLUDE_DIR ${OPENSSL_INSTAL_DIR}/include)
    set(OPENSSL_CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/config)
    include(ExternalProject)
    ExternalProject_Add(
        OpenSSL
        SOURCE_DIR ${OPENSSL_SOURCE_DIR}
        URL https://github.com/openssl/openssl/releases/download/openssl-${OPENSSL_VERSION}/openssl-${OPENSSL_VERSION}.tar.gz
        USES_TERMINAL_DOWNLOAD TRUE
        CONFIGURE_COMMAND
            ${OPENSSL_CONFIGURE_COMMAND}
            --prefix=${OPENSSL_INSTALL_DIR}
            --openssldir=${OPENSSL_INSTALL_DIR}
        BUILD_COMMAND make
        TEST_COMMAND ""
        INSTALL_COMMAND make install
        INSTALL_DIR ${OPENSSL_INSTALL_DIR}
        UPDATE_COMMAND ""
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )
endfunction(LibOpenSSL)
# Read this :: ->
# https://github.com/msys2/MINGW-packages/blob/master/mingw-w64-openssl/PKGBUILD'
# https://github.com/openssl/openssl/discussions/23469 for 3.3.1
# https://github.com/openssl/openssl/issues/5557