cmake_minimum_required(VERSION 3.8)

include(ExternalProject)

# Macro to build and install OpenCV statically
macro(LibOpenCV OPENCV_VERSION)
    # Set directories for source, build, and install
    set(OPENCV_SOURCE_DIR ${CMAKE_BINARY_DIR}/opencv_source)
    set(OPENCV_CONTRIB_DIR ${CMAKE_BINARY_DIR}/opencv_contrib)
    set(OPENCV_BUILD_DIR ${CMAKE_BINARY_DIR}/opencv_build)
    set(OPENCV_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)

    # ExternalProject to handle OpenCV contrib modules
    ExternalProject_Add(opencv_contrib
        PREFIX ${CMAKE_BINARY_DIR}/opencv_contrib_project
        GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git
        GIT_TAG ${OPENCV_VERSION}
        SOURCE_DIR ${OPENCV_CONTRIB_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
    )

    # ExternalProject to handle OpenCV from tar.gz release
    ExternalProject_Add(opencv
        PREFIX ${CMAKE_BINARY_DIR}/opencv_project
        URL https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Ensures extracted files use current timestamp
        SOURCE_DIR ${OPENCV_SOURCE_DIR}
        BINARY_DIR ${OPENCV_BUILD_DIR}
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
                -DBUILD_SHARED_LIBS=OFF
                -DBUILD_opencv_world=OFF
                -DBUILD_EXAMPLES=OFF
                -DBUILD_TESTS=OFF
                -DBUILD_PERF_TESTS=OFF
                -DOPENCV_ENABLE_NONFREE=ON
                -DOPENCV_EXTRA_MODULES_PATH=${OPENCV_CONTRIB_DIR}/modules
                -DCMAKE_INSTALL_PREFIX=${OPENCV_INSTALL_DIR}
                -DPYTHON_EXECUTABLE=/usr/bin/python3
                -Wno-dev
        INSTALL_COMMAND make install
        STEP_TARGETS install
    )

    # Ensure opencv_contrib is cloned before configuring opencv
    add_dependencies(opencv opencv_contrib)

    # Set environment variables and CMake prefix path for OpenCV
    ExternalProject_Get_Property(opencv install_dir)
    set(ENV{OpenCV_DIR} "${install_dir}/share/OpenCV")
    list(APPEND CMAKE_PREFIX_PATH "${install_dir}/share/OpenCV")

    # Add a custom target to trigger the build and install process
    add_custom_target(BuildAndInstall_OpenCV ALL
        DEPENDS opencv
        COMMENT "Building and installing OpenCV version ${OPENCV_VERSION}"
    )
endmacro(LibOpenCV)

# To use the macro inside the CMakeLists.txt
# Example usage: LibOpenCV("4.7.0")
