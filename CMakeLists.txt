CMAKE_MINIMUM_REQUIRED(VERSION 3.27)

project(HelloWorld
        LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD  20)

add_subdirectory(extern/glfw)

SET(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw opengl32)
