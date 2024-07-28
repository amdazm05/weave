include(Catch2Utils)
include(Libcurl)
include(LibOpenSSL)
# Test for presence of catch2 compilability
CompileTestFile(001-catch2_dep_test ${CMAKE_SOURCE_DIR}/tests/001-catch2_dep_test.cc)

CompileTestFile(002-openssl_dep_test ${CMAKE_SOURCE_DIR}/tests/002-openssl_dep_test.cc)
LinkAndIncludeOpenSSLToExecutable(002-openssl_dep_test)

CompileTestFile(003-libcurl_dep_test ${CMAKE_SOURCE_DIR}/tests/003-libcurl_dep_test.cc)
LinkAndIncludeLibCurlToExecutable(003-libcurl_dep_test)