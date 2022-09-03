cmake_minimum_required(VERSION 3.19)
project(p3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p3
        Board.hpp
        BoardValues.hpp
        Direction.hpp
        Game.hpp
        Ship.hpp
        StudentBoard.cpp
        StudentGame.cpp)
