cmake_minimum_required(VERSION 3.5)
project(svnzillion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        api.h
        common.h
        display.c
        display.h
        help.c
        housedeal.c
        housedeal.h
        richman.c
        richman.h
        test.c)

add_executable(zillion ${SOURCE_FILES})
