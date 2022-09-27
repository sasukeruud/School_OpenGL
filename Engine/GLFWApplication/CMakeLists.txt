cmake_minimum_required(VERSION 3.15)

project(GLFWApplication)        


#add_executable(          
#  GLFWApplication            
#  GLFWApplication.cpp                                        
#)



add_library(GLFWApplication GLFWApplication.h GLFWApplication.cpp)
add_library(Engine::GLFWApplication ALIAS GLFWApplication)
target_include_directories(GLFWApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(GLFWApplication PRIVATE TCLAP)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

