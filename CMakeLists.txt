cmake_minimum_required(VERSION 3.17)
project(WaterSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(WaterSort main.cpp GameState.h Tube.h Tube.cpp GameState.cpp Solver.h Solver.cpp)