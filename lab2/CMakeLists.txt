cmake_minimum_required(VERSION 3.15) 
project(chessBoard)       

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Fix the output directory for the archive artifacts [8]
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Fix the output directory for libraries [9]
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Fix the output directory for runtime files [10]

add_subdirectory(chessBoard)

