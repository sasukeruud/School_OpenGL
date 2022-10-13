cmake_minimum_required(VERSION 3.15)

project(Shader)

add_library(Shader Shader.h Shader.cpp)
add_library(Engine::GLFWApplication ALIAS GLFWApplication)
target_include_directories(GLFWApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)