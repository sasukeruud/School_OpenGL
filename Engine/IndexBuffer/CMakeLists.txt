cmake_minimum_required(VERSION 3.15)

project(IndexBuffer)

add_library(IndexBuffer IndexBuffer.h IndexBuffer.cpp)
add_library(Engine::IndexBuffer ALIAS IndexBuffer)
target_include_directories(IndexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE VertexBuffer)
target_link_libraries(${PROJECT_NAME} PRIVATE GeometricTools)