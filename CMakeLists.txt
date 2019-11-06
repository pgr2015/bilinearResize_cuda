cmake_minimum_required(VERSION 3.9)

#path to opencv build directory
set(OpenCV_DIR /home/pgr/opencv/build)
set(OpenCV_INCLUDES ${OpenCV_DIR}/include)


set(PROJECT example)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_STATIC OFF)
find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)
enable_language(CUDA) 

set(SOURCES
	test.cpp
	resize_cpu.cpp
	resize_gpu.cu
)

include_directories(
	${OpenCV_INCLUDES}
	${CUDA_INCLUDES}
	/usr/local/cuda/include
)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH TRUE)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT}
	${OpenCV_LIBS} 
	${CUDA_LIBRARIES}
)

