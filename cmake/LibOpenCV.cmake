
# Macro to build and install OpenCV statically]
macro(LibOpenCV OPENCV_VERSION)
    # Set directories for source, build, and install
    set(OPENCV_SOURCE_DIR ${CMAKE_BINARY_DIR}/opencv-src)
    set(OPENCV_BUILD_DIR ${CMAKE_BINARY_DIR}/opencv_build)
    set(OPENCV_INSTALL_DIR ${CMAKE_BINARY_DIR}/opencv)

    # ExternalProject to handle OpenCV contrib modules
    ExternalProject_Add(opencv
        PREFIX ${CMAKE_BINARY_DIR}/opencv_dir
		URL https://codeload.github.com/opencv/opencv/tar.gz/refs/tags/${OPENCV_VERSION}
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # Ensures extracted files use current timestamp
        DOWNLOAD_DIR ${OPENCV_SOURCE_DIR}
        INSTALL_DIR ${OPENCV_BUILD_DIR}
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
		-DBUILD_SHARED_LIBS=OFF
		-DBUILD_opencv_world=OFF
		-DWITH_GTK=ON 
		-DWITH_IPP=OFF 
		-DWITH_HALIDE=OFF
		-DWITH_VULKAN=OFF 
		-DWITH_INF_ENGINE=OFF 
		-DWITH_NGRAPH=OFF 
		-DWITH_JASPER=OFF 
		-DWITH_OPENJPEG=OFF 
		-DWITH_WEBP=OFF 
		-DWITH_OPENEXR=OFF 
		-DWITH_TIFF=OFF 
		-DWITH_OPENVX=OFF 
		-DWITH_GDCM=OFF 
		-DWITH_TBB=ON 
		-DWITH_HPX=OFF 
		-DWITH_EIGEN=OFF 
		-DWITH_V4L=ON 
		-DWITH_LIBV4L=ON 
		-DWITH_VTK=OFF 
		-DWITH_QT=OFF
		-DBUILD_opencv_python3=ON
		-DBUILD_opencv_java=OFF 
		-DBUILD_opencv_gapi=OFF
		-DBUILD_opencv_objc=OFF
		-DBUILD_opencv_js=OFF
		-DBUILD_opencv_ts=OFF 
		-DBUILD_opencv_dnn=OFF 
		-DBUILD_opencv_calib3d=OFF 
		-DBUILD_opencv_objdetect=OFF 
		-DBUILD_opencv_stitching=OFF 
		-DBUILD_opencv_ml=OFF 
		-DBUILD_opencv_world=OFF 
		-DBUILD_EXAMPLES=OFF 
		-DBUILD_EXAMPLES=OFF
		-DBUILD_TESTS=OFF
		-DBUILD_PERF_TESTS=OFF
		-DOPENCV_ENABLE_NONFREE=ON
		-DBUILD_opencv_contrib=OFF
		-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
		-DPYTHON_EXECUTABLE=/usr/bin/python3
        INSTALL_COMMAND make install
        STEP_TARGETS install
    )
	include_directories(${OPENCV_BUILD_DIR}/include/opencv4/)
	set(OpenCVLib_DIR ${OPENCV_BUILD_DIR}/lib/)
endmacro(LibOpenCV)


function(LinkAndIncludeOpenCVToExecutable NAME_EXE)
	# Replace with your OpenCV version
	target_link_libraries(${NAME_EXE} PRIVATE 
		${OpenCVLib_DIR}/libopencv_core.a
		${OpenCVLib_DIR}/opencv4/3rdparty/libittnotify.a
		${OpenCVLib_DIR}/opencv4/3rdparty/liblibjpeg-turbo.a
		${OpenCVLib_DIR}/opencv4/3rdparty/liblibpng.a
		${OpenCVLib_DIR}/opencv4/3rdparty/libzlib.a
		) 
endfunction(LinkAndIncludeOpenCVToExecutable)
# To use the macro inside the CMakeLists.txt
# Example usage: LibOpenCV("4.7.0")

