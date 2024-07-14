function(extract_libcurl)
    message(STATUS "Extracting libcurl...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_BINARY_DIR}/curl.tar.gz"
                   WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endfunction(extract_libcurl)