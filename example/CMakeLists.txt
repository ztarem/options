add_executable(options-example "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(options-example PRIVATE options::options)

add_test(plain options-example)
add_test(arg options-example -f 42)
add_test(verbose options-example -v)
add_test(quiet options-example -q)
