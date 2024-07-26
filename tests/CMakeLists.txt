include(Catch2Utils)
# Test for presence of catch2 compilability
CompileTestFile(001-catch2_dep_test ${CMAKE_SOURCE_DIR}/tests/001-catch2_dep_test.cc)
