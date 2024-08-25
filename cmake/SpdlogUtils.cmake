macro(Libspdlog spdlog_VERSION)
  set(spdlog_NAME "spdlog")
  set(spdlog_URL "https://github.com/gabime/spdlog/archive/refs/tags/${spdlog_VERSION}.tar.gz")
  set(spdlog_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/${spdlog_NAME}")
  set(spdlog_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${spdlog_NAME}-build")
  set(spdlog_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/${spdlog_NAME}-install")

  ExternalProject_Add(
    ${spdlog_NAME}
    PREFIX ${spdlog_SOURCE_DIR}
    URL ${spdlog_URL}
    DOWNLOAD_DIR ${spdlog_SOURCE_DIR}
    INSTALL_DIR ${spdlog_INSTALL_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        -DSPDLOG_INSTALL=ON
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  include_directories(${spdlog_INSTALL_DIR}/include)
endmacro(Libspdlog)

function(LinkAndIncludespdlogToExecutable NAME_EXE)
  target_link_libraries(${NAME_EXE} PRIVATE ${spdlog_INSTALL_DIR}//lib/libspdlog.a)
  target_include_directories(${NAME_EXE} PRIVATE ${spdlog_INSTALL_DIR}/include)
endfunction(LinkAndIncludespdlogToExecutable)