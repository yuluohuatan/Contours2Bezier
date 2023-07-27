cmake_minimum_required(VERSION 3.23)
project(Contours2Bezier)

set(CMAKE_CXX_STANDARD 17)

# set your opencv dir
set(OpenCV_DIR "${PROJECT_SOURCE_DIR}/3rdparty/opencv")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(Eigen3_DIR "${PROJECT_SOURCE_DIR}/3rdparty/eigen-3.3.9")
message(STATUS "Eigen3_DIR: ${Eigen3_DIR}")

include_directories(${Eigen3_DIR})

include_directories(include)

add_executable(Contours2Bezier main.cpp)
target_link_libraries(Contours2Bezier ${OpenCV_LIBS})
