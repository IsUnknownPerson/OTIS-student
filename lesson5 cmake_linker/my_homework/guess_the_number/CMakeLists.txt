cmake_minimum_required(VERSION 3.5)

project(guess_the_number LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(guess_the_number main.cpp
initgame.h initgame.cpp
gessing.h gessing.cpp
)

install(TARGETS guess_the_number
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
