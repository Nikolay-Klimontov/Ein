cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME stbimage)
project(${PROJECT_NAME} VERSION 2.16 DESCRIPTION "Image/texture loading library")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} stb_image.c)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})