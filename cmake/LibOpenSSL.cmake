function(LibOpenSSL OPENSSL_VERSION)
    set(OPENSSL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl-src) # default path by CMake
    set(OPENSSL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl)
    set(OPENSSL_INCLUDE_DIR ${OPENSSL_INSTALL_DIR}/include)
    set(OPENSSL_CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/config)
    include(ExternalProject)
    ExternalProject_Add(
        OpenSSL
        SOURCE_DIR ${OPENSSL_SOURCE_DIR}
        GIT_REPOSITORY https://github.com/openssl/openssl.git
        GIT_TAG openssl-3.3.1
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

    )
endfunction(LibOpenSSL)
# Read this :: ->
# https://github.com/msys2/MINGW-packages/blob/master/mingw-w64-openssl/PKGBUILD'
# https://github.com/openssl/openssl/discussions/23469 for 3.3.1
# https://github.com/openssl/openssl/issues/5557
