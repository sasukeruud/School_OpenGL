project(lab4)      

add_executable(    
  lab4      
  lab4.cpp            
  lab4.h
  main.cpp               
                        
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE GLFWApplication)
target_link_libraries(${PROJECT_NAME} PRIVATE GeometricTools)
target_link_libraries(${PROJECT_NAME} PRIVATE IndexBuffer)
target_link_libraries(${PROJECT_NAME} PRIVATE Shader)
target_link_libraries(${PROJECT_NAME} PRIVATE VertexArray)
target_link_libraries(${PROJECT_NAME} PRIVATE VertexBuffer)
target_link_libraries(${PROJECT_NAME} PRIVATE RenderCommands)
target_link_libraries(${PROJECT_NAME} PRIVATE stb)


target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_STATIC)


add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/wall.jpg
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/awsomeface.png)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  TEXTURES_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/")