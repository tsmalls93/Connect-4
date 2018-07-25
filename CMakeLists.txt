cmake_minimum_required(VERSION 3.10)
project(Connect_4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Connect_4
        AI.cpp
        AI.h
        Board.cpp
        Board.h
        main.cpp
        MainGame.cpp
        MainGame.h)
