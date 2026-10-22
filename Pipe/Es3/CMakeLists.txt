cmake_minimum_required(VERSION 3.28)
project(Es3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Es3 main.c)
target_link_libraries(Es3 PRIVATE m)
