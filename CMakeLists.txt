cmake_minimum_required(VERSION 3.1)
project(YOUR_PROJECT_NAME)

set(CMAKE_GXX_FLAGS "-Wall -Wextra -Wconversion  -pedantic -std=gnu11")

find_package(OpenCV REQUIRED)
find_package (Eigen3  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rrt rrt.cpp delete_.cpp)
add_executable(test delete.cpp delete_.cpp)
add_executable(grassfire grassfire.cpp)
add_executable(delete_ delete_.cpp)


target_link_libraries(rrt ${OpenCV_LIBS})
target_link_libraries(test ${OpenCV_LIBS})
target_link_libraries(grassfire ${OpenCV_LIBS} Eigen3::Eigen)
target_link_libraries(delete_ Eigen3::Eigen)