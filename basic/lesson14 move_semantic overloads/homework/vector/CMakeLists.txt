cmake_minimum_required(VERSION 3.5)

project(vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vector main.cpp
        mlist.cpp
        mvector.cpp
        vector_check.cpp
    list_check.cpp)


add_link_options(-fsanitize=address)
target_compile_options(
    vector PRIVATE    
    -Wall  -pedantic  -Wextra -Werror #-fsanitize=address
)

install(TARGETS vector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
