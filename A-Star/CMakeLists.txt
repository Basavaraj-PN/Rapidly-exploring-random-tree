cmake_minimum_required(VERSION 3.20)
project(A_Star)
set(CMAKE_GXX_FLAGS "-Wall -Wextra -Wconversion  -pedantic -std=gnu11")
set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
find_package (Eigen3  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(A_Star main.cpp)
target_link_libraries(A_Star ${OpenCV_LIBS} Eigen3::Eigen)