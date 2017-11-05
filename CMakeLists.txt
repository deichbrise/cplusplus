cmake_minimum_required(VERSION 3.8)
project(testate)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        testat1/break_words.c
        testat1/first_diff.c
        testat1/line_mean.c testat2/task1/easter.c testat2/task2/triangle_game.c)

add_executable(testate ${SOURCE_FILES})