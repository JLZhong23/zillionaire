cmake_minimum_required(VERSION 3.8)
project(richman)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES richman.c display.c housedeal.c common.h display.h richman.h housedeal.h)
add_executable(richman ${SOURCE_FILES})