include(Catch2Utils)
include(Libcurl)
include(LibOpenSSL)
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