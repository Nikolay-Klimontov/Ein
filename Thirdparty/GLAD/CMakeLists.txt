cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME glad)
project(${PROJECT_NAME} VERSION 1.0 DESCRIPTION "OpenGL Extension loader")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(${PROJECT_NAME} src/glad.c)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} dl)