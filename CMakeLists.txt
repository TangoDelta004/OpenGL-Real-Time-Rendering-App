cmake_minimum_required(VERSION 3.3)
project(LearnOpenGL-CLion)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Including GLFW
add_subdirectory(glfw)
include_directories(glfw/include)

# Including GLAD
include_directories(glad/include)

set(SOURCE_FILES glad/src/glad.c
        EBO.cpp
        shaderClass.cpp
        VAO.cpp
        VBO.cpp
        main.cpp
        EBO.h
        shaderClass.h
        VAO.h
        VBO.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
