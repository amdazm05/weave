cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0063 NEW) 
# Project version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(UNIT_TESTS TRUE)
set(PROJECT_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

project(weave VERSION ${PROJECT_VERSION})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

message("WEAVE_CMAKE_PROJECT_VERSION : ${PROJECT_VERSION}")

#Use includes and utilities here
include(Libcurl)
include(LibOpenSSL)
include(Catch2Utils)
include(RedisUtils)
include(SpdlogUtils)
LibOpenSSL("3.0.14")
LibCurlFetchInstall("8_8_0")
LibHIREDIS("v1.2.0")
FetchCatch2("3.6.0")
Libspdlog("v1.14.1")

include_directories(${PROJECT_SOURCE_DIR}/include)
file( GLOB WEAVE_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*/*.cc ${PROJECT_SOURCE_DIR}/src/*/*.cpp)

add_library(weave STATIC ${WEAVE_SOURCE_FILES})

# cmake_print_variables(UNIT_TESTS)
if(UNIT_TESTS)
    message("Tests Enabled for WEAVE ${PROJECT_VERSION} ")
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)    
endif()