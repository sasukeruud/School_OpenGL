cmake_minimum_required(VERSION 3.15)

project(Engine)

add_library(GLFWApplication GLFWApplication.h GLFWApplication.cpp)
add_library(Engine::GLFWApplication ALIAS GLFWApplication)
target_include_directories(GLFWApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
