cmake_minimum_required(VERSION 3.15)
project(Lab)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the external dependencies
add_subdirectory(External/tclap)
add_subdirectory(External/GLFW)
add_subdirectory(External/glad)

#########################
#add_subdirectory(Engine/GeometricTools)
#add_subdirectory(Engine/GLFWApplication)
#add_subdirectory(Engine/VertexBuffer)
#add_subdirectory(Engine/IndexBuffer)
add_subdirectory(Engine)

add_subdirectory(engineTest)
add_subdirectory(lab1/HelloOpenGL)
add_subdirectory(lab1/HelloOpenGL_v2)
add_subdirectory(lab1/Hello)
#add_subdirectory(lab2)