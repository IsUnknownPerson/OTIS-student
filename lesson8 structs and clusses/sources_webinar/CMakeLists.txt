cmake_minimum_required(VERSION 3.5)

project(08.Classes)

add_executable(01_structures structures.cpp)
set_target_properties(01_structures  PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

add_executable(02_struct_stream struct_stream.cpp)
set_target_properties(02_struct_stream PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(03_struct_operators struct_operators.cpp)
set_target_properties(03_struct_operators PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(04_class class.cpp complex.cpp)
set_target_properties(04_class PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if (UNIX)
add_executable(05_advanced_class advanced_class.cpp)
set_target_properties(05_advanced_class PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
endif()

add_executable(06_inheritance_spoiler inheritance_spoiler.cpp)
set_target_properties(06_inheritance_spoiler PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

add_executable(07_operator_overload operator_overload.cpp)
set_target_properties(07_operator_overload PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)




