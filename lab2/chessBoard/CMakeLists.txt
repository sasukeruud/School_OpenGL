project(chessBoard)      

add_executable(    
  chessBoard      
  chessBoard.cpp            
  chessBoard.h
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
