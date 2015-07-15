cmake_minimum_required(VERSION 3.2)
project(AFD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AFD ${SOURCE_FILES} Estado.cpp Estado.h Transicion.cpp Transicion.h)