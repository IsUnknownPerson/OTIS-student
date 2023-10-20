cmake_minimum_required(VERSION 3.5)

project(allocators LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(02_logging_allocator logging_allocator.cpp)

add_executable(01_std_03_allocator simple_allocator.cpp)

add_executable(00_new_overload new_overload.cpp)

add_executable(03_allocator_traits allocator_traits.cpp)

add_executable(04_polymorphism polymorphism.cpp)

add_executable(05_polymorphic_allocator polymorphic_allocator.cpp)

install(TARGETS 02_logging_allocator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS 01_std_03_allocator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS 00_new_overload
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS 03_allocator_traits
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS 04_polymorphism
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS 05_polymorphic_allocator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
