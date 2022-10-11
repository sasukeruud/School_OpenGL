project(GeometricTools)  

add_library(GeometricTools INTERFACE)
add_library(Engine::GeometricTools ALIAS GeometricTools)
target_include_directories(GeometricTools INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE glm)