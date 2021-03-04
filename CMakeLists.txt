cmake_minimum_required(VERSION 3.17)
project(WaterSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(WaterSort main.cpp Tube.h Tube.cpp Solver.h Solver.cpp)