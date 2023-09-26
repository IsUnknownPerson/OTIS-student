cmake_minimum_required(VERSION 3.7.2)
project(polymorphism)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

add_executable(accessibility_of_inherited_members 1.accessibility_of_inherited_members.cpp)
add_executable(inheritance.square-rect 2.inheritance.square-rect.cpp)
add_executable(inheritance.try-poly 3.inheritance.try-poly.cpp)
add_executable(virtual 4.virtual.cpp)

file(GLOB SHAPES_SOURCES 5.shapes/*.cpp)
add_executable(5.shapes ${SHAPES_SOURCES})