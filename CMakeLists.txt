CMAKE_MINIMUM_REQUIRED(VERSION 3.27)

project(HelloWorld
        LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD  20)

include_directories(extern/glad/include)
add_subdirectory(extern/glfw)

SET(SOURCES extern/glad/src/glad.c
                        main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
