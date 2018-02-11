cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME thirdparty)
project(${PROJECT_NAME})

#------------------------------------------#
#           Thirdparty stuff               #
#------------------------------------------#
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

add_subdirectory(GLAD)
add_subdirectory(STB)
