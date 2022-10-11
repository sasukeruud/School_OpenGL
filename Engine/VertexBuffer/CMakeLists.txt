cmake_minimum_required(VERSION 3.15)

project(VertexBuffer)

add_library(VertexBuffer VertexBuffer.h ShadersDataTypes.h Render.cpp)
add_library(Engine::VertexBuffer ALIAS VertexBuffer)
target_include_directories(VertexBuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glad)