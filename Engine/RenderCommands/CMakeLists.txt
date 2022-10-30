project(RenderCommands)

add_library(RenderCommands INTERFACE)
add_library(Engine::RenderCommands ALIAS RenderCommands)
target_include_directories(RenderCommands INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE glm)
target_link_libraries(${PROJECT_NAME} INTERFACE glad)
target_link_libraries(${PROJECT_NAME} INTERFACE VertexArray)