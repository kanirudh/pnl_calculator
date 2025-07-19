cmake_minimum_required(VERSION 3.20)
project(pnl_calculator)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(test)