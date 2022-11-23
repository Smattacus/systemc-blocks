cmake_minimum_required(VERSION 3.18)

include_directories("/usr/local/systemc-2.3.3/include/")
include_directories("/usr/local/systemc-ams-2.3/include/")

link_directories("/usr/local/systemc-2.3.3/lib-linux64/")
link_directories("/usr/local/systemc-ams-2.3/lib-linux64/")

link_libraries("libsystemc.a")
link_libraries("libsystemc-ams.a")

project(blocks)

add_executable(test_xor xor/test_xor.cpp)
add_executable(hello hello.cpp)
add_executable(test_stack stack/test_stack.cpp)
add_executable(sharpener sharpener/test_sharpener.cpp)