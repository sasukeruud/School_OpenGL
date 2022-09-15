cmake_minimum_required(VERSION 3.15)
project(Lab_work)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the external dependencies
add_subdirectory(external/tclap)
add_subdirectory(external/GLFW)
add_subdirectory(external/glad)

add_subdirectory(Engine)
#add_subdirectory(Engine) # For the lab to be used to make a project of