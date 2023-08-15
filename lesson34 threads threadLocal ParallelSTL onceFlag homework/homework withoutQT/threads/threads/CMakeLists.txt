cmake_minimum_required(VERSION 3.5)

project(threads LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(one_thread one_thread.cpp)
add_executable(multi_thread multi_thread.cpp)

install(TARGETS
    one_thread
    multi_thread
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
