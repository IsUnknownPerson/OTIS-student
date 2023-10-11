cmake_minimum_required(VERSION 3.5)

project(03.cpp)

add_executable(previous previous.cpp)
add_executable(rvo rvo.cpp)
add_executable(values values.cpp)
add_executable(move move.cpp)
add_executable(move_additional move_additional.cpp)
add_executable(additional additional.cpp)
add_executable(vt vt.cpp)

set_target_properties(rvo values move vt PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

set_target_properties(move_additional PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

set_target_properties(additional PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(move_cpp98 move_cpp98.cpp)
set_target_properties(move_cpp98 PROPERTIES
        CXX_STANDARD 98
        CXX_STANDARD_REQUIRED ON
)
add_executable(move_cpp11 move_cpp11.cpp)
set_target_properties(move_cpp11 PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

add_executable(move_custom_str_cpp98 move_custom_str_cpp98.cpp)
set_target_properties(move_custom_str_cpp98 PROPERTIES
        CXX_STANDARD 98
        CXX_STANDARD_REQUIRED ON
)
add_executable(move_custom_str_cpp11 move_custom_str_cpp11.cpp)
set_target_properties(move_custom_str_cpp11 PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

