cmake_minimum_required(VERSION 3.12)

project(04.Functions)

add_executable(arithm_operations     arithm_operations.cpp)
add_executable(type_ranges_float     type_ranges_float.cpp)
add_executable(type_ranges_int       type_ranges_int.cpp)

set_target_properties(
        arithm_operations
        type_ranges_float
        type_ranges_int
PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
