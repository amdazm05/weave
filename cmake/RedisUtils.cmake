macro(LibHIREDIS HIREDIS_VERSION)
  set(HIREDIS_NAME "hiredis")
  set(HIREDIS_URL "https://github.com/redis/hiredis/archive/refs/tags/${HIREDIS_VERSION}.tar.gz")
  set(HIREDIS_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/${HIREDIS_NAME}")
  set(HIREDIS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${HIREDIS_NAME}-build")
  set(HIREDIS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/${HIREDIS_NAME}-install")

  ExternalProject_Add(
    ${HIREDIS_NAME}
    PREFIX ${HIREDIS_SOURCE_DIR}
    URL ${HIREDIS_URL}
    DOWNLOAD_DIR ${HIREDIS_SOURCE_DIR}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND make install DESTDIR=${HIREDIS_INSTALL_DIR}
    INSTALL_DIR ${HIREDIS_INSTALL_DIR}
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  include_directories(${HIREDIS_INSTALL_DIR}/usr/local/include)
endmacro(LibHIREDIS)

function(LinkAndIncludeHiredisToExecutable NAME_EXE)
  target_link_libraries(${NAME_EXE} PRIVATE ${HIREDIS_INSTALL_DIR}/usr/local/lib/libhiredis.a)
  target_include_directories(${NAME_EXE} PRIVATE ${HIREDIS_INSTALL_DIR}/usr/local/include)
endfunction(LinkAndIncludeHiredisToExecutable)
