cmake_minimum_required(VERSION 3.28)
project(Es3ProvoIo C)

set(CMAKE_C_STANDARD 11)

add_executable(Es3ProvoIo PING.c
        PONG.c)
