cmake_minimum_required(VERSION 3.3)
project(LearnOpenGL-CLion)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(libraries/lib/glfw)
include_directories(libraries/include)

set(SOURCE_FILES
        EBO.cpp
        shaderClass.cpp
        VAO.cpp
        VBO.cpp
        main.cpp
        EBO.h
        shaderClass.h
        VAO.h
        VBO.h
        glad.c
        libraries/include/stb/stb_image.h
        stb.cpp
        texture.cpp
        texture.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
