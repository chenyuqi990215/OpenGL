cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL main.cpp point.cpp point.h surface.cpp surface.h model.cpp model.h)
target_link_libraries(OpenGL opengl32 glu32 freeglut)