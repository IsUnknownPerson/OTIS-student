cmake_minimum_required(VERSION 3.12)

project(OtusCppWeb10 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED)

add_executable(server_callback coroutines/callback_async_server.cpp)
target_link_libraries(server_callback Boost::boost)
add_executable(server_coroutine coroutines/coroutine_async_server.cpp)
target_link_libraries(server_coroutine Boost::boost)
add_executable(timers coroutines/timers.cpp)

add_executable(spaceship spaceship/main.cpp)

add_executable(no_concepts concepts/no_concepts.cpp)
add_executable(concepts concepts/main.cpp)

add_executable(ranges ranges/main.cpp)

add_executable(format format/main.cpp)
