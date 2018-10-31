cmake_minimum_required(VERSION 3.8)
project(zillionaire)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        common.h
        display.c
        display.h
        housedeal.c
        housedeal.h
        richman.c
        richman.h input.c api.h help.c)

add_executable(zillionaire ${SOURCE_FILES})