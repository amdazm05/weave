include(Catch2Utils)
include(Libcurl)
include(LibOpenSSL)
include(LibOpenCV)
enable_testing()

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/tests/*.cc 
    ${PROJECT_SOURCE_DIR}/tests/*.cc)

foreach(TEST_FILE_PATH ${TEST_SOURCES})
        cmake_path(GET TEST_FILE_PATH FILENAME TESTNAME_WITHEXT)
        cmake_path(GET TESTNAME_WITHEXT STEM TEST_NAME  )
        message("Test Name : ${TEST_NAME}")
        CompileTestFile(${TEST_NAME} ${TEST_FILE_PATH})
        target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME})
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
    