cmake_minimum_required(VERSION 3.15)

project(TextureManager)       


add_library(TextureManager TextureManager.h TextureManager.cpp)
add_library(Engine::TextureManager ALIAS TextureManager)
target_include_directories(TextureManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)


target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_STATIC)