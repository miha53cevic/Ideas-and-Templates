cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
project(cmake_example)

file(GLOB SOURCES "./*.cpp")

add_executable(example ${SOURCES})