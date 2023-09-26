cmake_minimum_required(VERSION 3.5)

project(idioms-2)

set (CMAKE_CXX_STANDARD 17 REQUIRED)

add_executable(self_assignment self_assignment.cpp)
add_subdirectory(pimpl)
add_executable(virtual_ctor virtual_ctor.cpp)
add_executable(mixin mixin.cpp)

find_package(Threads)
add_executable(shared_from_this shared_from_this.cpp)
target_link_libraries(shared_from_this PRIVATE Threads::Threads)
add_executable(singleton singleton.cpp)