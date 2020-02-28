cmake_minimum_required(VERSION 3.10)

project(options VERSION 0.1.0)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

add_subdirectory(src)
add_subdirectory(example)
