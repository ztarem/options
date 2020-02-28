add_executable(options-example "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(options-example PRIVATE options::options)
