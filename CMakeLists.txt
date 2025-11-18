CMAKE_MINIMUM_REQUIRED(VERSION 3.27)

project(HelloWorld
        LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD  20)

include_directories(extern/glad/include)
include_directories(extern/stb)
include_directories(src/renderer)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)

SET(SOURCES extern/glad/src/glad.c
           src/renderer/shader.cpp
                        main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm) 
target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)
