include(Catch2Utils)
include(Libcurl)
include(LibOpenSSL)
include(LibOpenCV)
enable_testing()
# Test for presence of catch2 compilability
CompileTestFile(001-catch2_dep_test ${CMAKE_SOURCE_DIR}/tests/001-catch2_dep_test.cc)

CompileTestFile(002-openssl_dep_test ${CMAKE_SOURCE_DIR}/tests/002-openssl_dep_test.cc)
LinkAndIncludeOpenSSLToExecutable(002-openssl_dep_test)

CompileTestFile(003-libcurl_dep_test ${CMAKE_SOURCE_DIR}/tests/003-libcurl_dep_test.cc)
LinkAndIncludeLibCurlToExecutable(003-libcurl_dep_test)

CompileTestFile(004-hiredis_dep_test ${CMAKE_SOURCE_DIR}/tests/004-hiredis_dep_test.cc)
LinkAndIncludeHiredisToExecutable(004-hiredis_dep_test)

CompileTestFile(005-spdlog_dep_test ${CMAKE_SOURCE_DIR}/tests/005-spdlog_dep_test.cc)
LinkAndIncludespdlogToExecutable(005-spdlog_dep_test)

# CompileTestFile(007-opencv_dep_test ${CMAKE_SOURCE_DIR}/tests/007-opencv_dep_test.cc)
# target_link_libraries(007-opencv_dep_test PRIVATE ${OpenCV_LIBS})

# TODO restructure this
CompileTestFile(006-http_uri_tests ${CMAKE_SOURCE_DIR}/tests/006-http_uri_tests.cc)
target_link_libraries(006-http_uri_tests PRIVATE ${PROJECT_NAME})

CompileTestFile(008-http_protocol_entity_tests
	${CMAKE_SOURCE_DIR}/tests/008-http_protocol_entity_tests.cc)
target_link_libraries(008-http_protocol_entity_tests PRIVATE ${PROJECT_NAME})

CompileTestFile(009-singleton-contexts
	${CMAKE_SOURCE_DIR}/tests/009-singleton-contexts.cc)
target_link_libraries(009-singleton-contexts PRIVATE ${PROJECT_NAME})

CompileTestFile(010-curlhandler-request-tests
	${CMAKE_SOURCE_DIR}/tests/010-curlhandler-request-tests.cc)
target_link_libraries(010-curlhandler-request-tests PRIVATE ${PROJECT_NAME})

CompileTestFile(011-curl-set-headers
	${CMAKE_SOURCE_DIR}/tests/011-curl-set-headers.cc)
target_link_libraries(011-curl-set-headers PRIVATE ${PROJECT_NAME})

# Dependancy Tests
add_test(NAME 001-catch2_dep_test
         COMMAND 001-catch2_dep_test)
add_test(NAME 002-openssl_dep_test
         COMMAND 002-openssl_dep_test)
add_test(NAME 003-libcurl_dep_test
         COMMAND 003-libcurl_dep_test)
add_test(NAME 004-hiredis_dep_test
         COMMAND 004-hiredis_dep_test)
add_test(NAME 005-spdlog_dep_test
         COMMAND 005-spdlog_dep_test)
add_test(NAME 006-http_uri_tests
         COMMAND 006-http_uri_tests)
# add_test(NAME 007-opencv_dep_test
#          COMMAND 007-opencv_dep_test)