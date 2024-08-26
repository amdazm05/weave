cmake_minimum_required(VERSION 3.8)

# Building and installing OpenCV statically
macro(BuildAndInstallOpenCV OPENCV_VERSION)
    # Setting CV directories
    set(OPENCV_SOURCE_DIR ${CMAKE_BINARY_DIR}/opencv_source)
    set(OPENCV_CONTRIB_DIR ${CMAKE_BINARY_DIR}/opencv_contrib)
    set(OPENCV_BUILD_DIR ${CMAKE_BINARY_DIR}/opencv_build)
    set(OPENCV_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)

    # Cloning OpenCV and OpenCV contrib repositories from their official repositories 
    if(NOT EXISTS "${OPENCV_SOURCE_DIR}")
        execute_process(
            COMMAND git clone --branch ${OPENCV_VERSION} https://github.com/opencv/opencv.git ${OPENCV_SOURCE_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    if(NOT EXISTS "${OPENCV_CONTRIB_DIR}")
        execute_process(
            COMMAND git clone --branch ${OPENCV_VERSION} https://github.com/opencv/opencv_contrib.git ${OPENCV_CONTRIB_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    file(MAKE_DIRECTORY ${OPENCV_BUILD_DIR})

    # Configuring the OpenCV build
    execute_process(
        COMMAND cmake -DCMAKE_BUILD_TYPE=Release
                      -DBUILD_SHARED_LIBS=OFF # Incase you want dynamic libraries, rmove this line
                      -DBUILD_opencv_world=OFF
                      -DBUILD_EXAMPLES=OFF
                      -DBUILD_TESTS=OFF
                      -DBUILD_PERF_TESTS=OFF
                      -DOPENCV_ENABLE_NONFREE=ON
                      -DOPENCV_EXTRA_MODULES_PATH=${OPENCV_CONTRIB_DIR}/modules
                      -DCMAKE_INSTALL_PREFIX=${OPENCV_INSTALL_DIR}
                      ${OPENCV_SOURCE_DIR}
        WORKING_DIRECTORY ${OPENCV_BUILD_DIR}
    )

    # Building 
    execute_process(
        COMMAND make -j$(nproc)
        WORKING_DIRECTORY ${OPENCV_BUILD_DIR}
    )

    # Installing 
    execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${OPENCV_BUILD_DIR}
    )

    message(STATUS "OpenCV installed to: ${OPENCV_INSTALL_DIR}")

    # Setting the environment variable and CMake prefix path for OpenCV
    set(ENV{OpenCV_DIR} "${OPENCV_INSTALL_DIR}/share/OpenCV")
    list(APPEND CMAKE_PREFIX_PATH "${OPENCV_INSTALL_DIR}/share/OpenCV")
endmacro(BuildAndInstallOpenCV)

# To use the macro inside the CMakeLists.txt
# BuildAndInstallOpenCV("4.7.0")
