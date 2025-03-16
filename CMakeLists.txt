cmake_minimum_required(VERSION 3.10)
project(lucy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES Servers/*.cpp Sockets/*.cpp Middlewares/*.cpp)

add_executable(lucy ${SOURCES})

set(CMAKE_BUILD_TYPE Debug)
