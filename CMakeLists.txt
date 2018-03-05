CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
SET(PROJECT_NAME ein)
PROJECT(${PROJECT_NAME})

ADD_SUBDIRECTORY(Thirdparty)

SET(CMAKE_CXX_STANDARD 17)
#--------------------------------------------------------------
SET(RENDERING_SUBYSTEM_PATH Subsystems/Rendering)

SET(RENDERING_SUBYSTEM
    ${RENDERING_SUBYSTEM_PATH}/Resources/shaders.hpp
    ${RENDERING_SUBYSTEM_PATH}/Resources/shaders.cpp
    ${RENDERING_SUBYSTEM_PATH}/Resources/geometry.cpp
    ${RENDERING_SUBYSTEM_PATH}/Resources/geometry.hpp
    ${RENDERING_SUBYSTEM_PATH}/Resources/texture.cpp
    ${RENDERING_SUBYSTEM_PATH}/Resources/texture.hpp
    ${RENDERING_SUBYSTEM_PATH}/camera.cpp
    ${RENDERING_SUBYSTEM_PATH}/camera.hpp
   )
#--------------------------------------------------------------
SET(UTILITY_PATH Utility)

SET(UTILITY
    ${UTILITY_PATH}/logger.hpp
    ${UTILITY_PATH}/templates.hpp
    ${UTILITY_PATH}/readers.hpp
    ${UTILITY_PATH}/readers.cpp
    ${UTILITY_PATH}/GL.hpp
    ${UTILITY_PATH}/GLFW.hpp
    ${UTILITY_PATH}/types.hpp
    ${UTILITY_PATH}/types.cpp)

INCLUDE_DIRECTORIES(${UTILITY_PATH})
#--------------------------------------------------------------
SET(SOURCES main.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${RENDERING_SUBYSTEM} ${UTILITY})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES} glad stbimage)
