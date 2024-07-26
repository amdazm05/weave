function(FetchCatch2 CATCH2_VERSION)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v${CATCH2_VERSION} # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
endfunction(FetchCatch2)

function(CompileTestFile TEST_NAME FILE_PATH)
    find_package(Catch2 REQUIRED)
    add_executable(${TEST_NAME} ${FILE_PATH})
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2)
endfunction(CompileTestFile FILE_PATH)
