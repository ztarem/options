cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(options VERSION 0.2.0)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)
enable_testing()

add_subdirectory(src)
add_subdirectory(example)
#add_subdirectory(tests)
