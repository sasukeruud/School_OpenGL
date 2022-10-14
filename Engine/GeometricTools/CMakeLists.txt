project(GeometricTools)  

add_library(GeometricTools INTERFACE)
add_library(Engine::GeometricTools ALIAS GeometricTools)
add_library(ColorTools INTERFACE)
add_library(Engine::ColorTools ALIAS ColorTools)
target_include_directories(GeometricTools INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE glm)