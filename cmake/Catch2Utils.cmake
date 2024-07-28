macro(FetchCatch2 CATCH2_VERSION)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v${CATCH2_VERSION} # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
    message("${catch2_SOURCE_DIR}")
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endmacro(FetchCatch2)

function(CompileTestFile TEST_NAME FILE_PATH)
    include(CTest)
    include(Catch)
    add_executable(${TEST_NAME} ${FILE_PATH})
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
endfunction(CompileTestFile FILE_PATH)

# Documentation
# Refer to https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md