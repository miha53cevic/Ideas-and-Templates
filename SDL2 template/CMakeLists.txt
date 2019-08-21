cmake_minimum_required(VERSION 3.10)

# Name of the project
project(SDL2_example)

# Put executable inside of bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set source .cpp files
set(SOURCES 
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Use C++17 standard 
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Find SDL2
find_package(SDL2 REQUIRED)

# Add SDL2 to include directories
include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})