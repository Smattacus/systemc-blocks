cmake_minimum_required(VERSION 3.18)

include_directories("/usr/local/systemc-2.3.3/include/")
include_directories("/usr/local/systemc-ams-2.3/include/")
include_directories("/usr/include/libpng16/png.h")
include_directories("/sharpener")


link_directories("/usr/local/systemc-2.3.3/lib-linux64/")
link_directories("/usr/local/systemc-ams-2.3/lib-linux64/")
link_directories("/usr/bin/lib/x86_64-linux-gnu")

link_libraries("libsystemc.a")
link_libraries("libsystemc-ams.a")
link_libraries("libpng.a")
link_libraries("libz.a")

add_library(source sharpener/source.cpp)
add_library(sink sharpener/sink.cpp)
add_library(sharpener sharpener/sharpener.cpp)

project(blocks)

add_executable(test_xor xor/test_xor.cpp)
add_executable(hello hello.cpp)
add_executable(test_stack stack/test_stack.cpp)
add_executable(test_sharpener sharpener/test_sharpener.cpp)

target_link_libraries(test_sharpener sharpener source sink)
