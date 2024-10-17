macro(LibAsioFetch ASIO_VERSION)
    set(ASIO_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/asio-src)
    set(ASIO_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/asio)
    set(ASIO_INCLUDE_DIR ${ASIO_INSTALL_DIR}/include)
    ExternalProject_Add(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG ${ASIO_VERSION}
        SOURCE_DIR ${ASIO_SOURCE_DIR}
        USES_TERMINAL_DOWNLOAD TRUE
        CONFIGURE_COMMAND cd ${ASIO_SOURCE_DIR}/asio && 
            ./autogen.sh &&
            ./configure  --with-boost=no --prefix=${ASIO_INSTALL_DIR}
        BUILD_COMMAND cd ${ASIO_SOURCE_DIR}/asio && make 
        INSTALL_COMMAND cd ${ASIO_SOURCE_DIR}/asio && make install
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )
endmacro(LibAsioFetch)

function(LibAsioTargetInclude NAME_EXE)
  target_include_directories(${NAME_EXE} PRIVATE ${LIBCURL_SOURCE_DIR}/include)
endfunction(LibAsioTargetInclude)