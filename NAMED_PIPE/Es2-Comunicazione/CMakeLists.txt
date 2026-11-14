cmake_minimum_required(VERSION 3.28)
project(Es2_Comunicazione C)

set(CMAKE_C_STANDARD 11)

add_executable(Es2_Comunicazione writer.c
        reader.c)
