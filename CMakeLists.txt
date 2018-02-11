cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME ein)
project(${PROJECT_NAME})

add_subdirectory(Thirdparty)

set(CMAKE_CXX_STANDARD 17)
#--------------------------------------------------------------
set(RENDERING_SUBYSTEM_PATH Subsystems/Rendering)

set(RENDERING_SUBYSTEM
        ${RENDERING_SUBYSTEM_PATH}/Resources/shaders.hpp
        ${RENDERING_SUBYSTEM_PATH}/Resources/shaders.cpp Subsystems/Rendering/Resources/geometry.cpp Subsystems/Rendering/Resources/geometry.hpp Subsystems/Rendering/Resources/texture.cpp Subsystems/Rendering/Resources/texture.hpp Subsystems/Rendering/camera.cpp Subsystems/Rendering/camera.hpp)
#--------------------------------------------------------------
set(UTILITY_PATH Utility)

set(UTILITY
    ${UTILITY_PATH}/logger.hpp
    ${UTILITY_PATH}/templates.hpp Utility/readers.hpp Utility/readers.cpp Utility/GL.hpp Utility/GLFW.hpp Utility/types.hpp)

include_directories( ${UTILITY_PATH})
#--------------------------------------------------------------
set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${RENDERING_SUBYSTEM} ${UTILITY})
target_link_libraries(${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES} glad stbimage)
