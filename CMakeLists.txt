cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(options VERSION 0.2.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()

add_subdirectory(src)
add_subdirectory(example)
#add_subdirectory(tests)
