cmake_minimum_required(VERSION 3.19)

project(sdl2gl)

set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD_REQUIRED 17)

# OpenGL
find_package(OpenGL REQUIRED)

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL SDL2::SDL2)
