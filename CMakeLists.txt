cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(show_image)
add_executable(show_image show_image.cpp)

project(gray_image)
add_executable(gray_image gray_image.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(show_image PRIVATE ${OpenCV_LIBS})
target_link_libraries(gray_image PRIVATE ${OpenCV_LIBS})