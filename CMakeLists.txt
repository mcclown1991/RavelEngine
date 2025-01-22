cmake_minimum_required(VERSION 3.25)
project(RavelEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_TEST "Build as exe" OFF)

SET(DEFINES -DUNICODE -D_UNICODE)
add_definitions(${DEFINES})

add_subdirectory("Ravel Engine")
#add_subdirectory("Main Unit Test")