macro(LibOpenSSL OPENSSL_VERSION)
    set(OPENSSL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl-src) # default path by CMake
    set(OPENSSL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl)
    set(OPENSSL_INCLUDE_DIR ${OPENSSL_INSTAL_DIR}/include)
    set(OPENSSL_CONFIGURE_COMMAND ${OPENSSL_SOURCE_DIR}/Configure linux-x86_64)
    include(ExternalProject)
    ExternalProject_Add(
        OpenSSL
        SOURCE_DIR ${OPENSSL_SOURCE_DIR}
        URL https://github.com/openssl/openssl/releases/download/openssl-${OPENSSL_VERSION}/openssl-${OPENSSL_VERSION}.tar.gz
        USES_TERMINAL_DOWNLOAD TRUE
        CONFIGURE_COMMAND
            ${OPENSSL_CONFIGURE_COMMAND} 
            # Discussion here //some systems might build in lib64
            # https://github.com/openssl/openssl/issues/16244
            # https://github.com/curl/curl/pull/8536
            no-tests 
            --libdir=lib
            --prefix=${OPENSSL_INSTALL_DIR}
            --openssldir=${OPENSSL_INSTALL_DIR}
        BUILD_COMMAND make
        TEST_COMMAND ""
        INSTALL_COMMAND make install_sw
        INSTALL_DIR ${OPENSSL_INSTALL_DIR}
        UPDATE_COMMAND ""
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )
endmacro(LibOpenSSL)

macro(LinkAndIncludeOpenSSLToExecutable NAME_EXE)
  target_link_libraries(${NAME_EXE} PRIVATE ${OPENSSL_INSTALL_DIR}/lib64/libssl.a ${OPENSSL_INSTALL_DIR}/lib64/libcrypto.a)
  target_include_directories(${NAME_EXE} PRIVATE ${CMAKE_BINARY_DIR}/openssl/include)
endmacro(LinkAndIncludeOpenSSLToExecutable)

# Read this :: ->
# https://github.com/msys2/MINGW-packages/blob/master/mingw-w64-openssl/PKGBUILD'
# https://github.com/openssl/openssl/discussions/23469 for 3.3.1
# https://github.com/openssl/openssl/issues/5557
# https://github.com/anthonybilinski/qTox/commit/602654f73fcf93d82022b0595f23c39eaf0f8078
# unecessary to build docs here