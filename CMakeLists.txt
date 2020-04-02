cmake_minimum_required(VERSION 3.16)

project(Paint VERSION "1.0.0")

message(STATUS "This is from the C:/dev/Paint directory")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/dependencies/SDL2/include)

add_subdirectory(src)