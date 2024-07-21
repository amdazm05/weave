cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0063 NEW) 
# Project version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(PROJECT_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

project(weave VERSION ${PROJECT_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Sets the path to CMake custom modules
set(OLD_CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

message("WEAVE_CMAKE_PROJECT_VERSION : ${PROJECT_VERSION}")

#Use includes and utilities here
include(Libcurl)
include(LibOpenSSL)
LibOpenSSL("3.0.14")
LibCurlFetchInstall("8_8_0")

#Restore Module Path once done
set(CMAKE_MODULE_PATH ${OLD_CMAKE_MODULE_PATH})