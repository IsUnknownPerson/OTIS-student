cmake_minimum_required(VERSION 3.5)

project(Hello_world LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Hello_world main.cpp
move_me_out.h move_me_out.cpp)

install(TARGETS Hello_world
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
