cmake_minimum_required(VERSION 3.15)

project(VertexArray)

add_library(VertexArray VertexArray.h VertexArray.cpp)
add_library(Engine::VertexArray ALIAS VertexArray)
target_include_directories(VertexArray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE VertexBuffer)
target_link_libraries(${PROJECT_NAME} PRIVATE IndexBuffer)