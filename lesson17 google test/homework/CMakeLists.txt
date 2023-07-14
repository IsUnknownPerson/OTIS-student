cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(UNITtest LANGUAGES CXX)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    #By default, new Visual Studio projects link the C runtimes dynamically
    #but GoogleTest links them statically. This will generate an error
    #Enabling this option will make gtest link the runtimes dynamically too
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)


# Main target
add_executable(vector vector/main.cpp
        vector/mlist.cpp
        vector/mvector.cpp
        vector/vector_check.cpp
    vector/list_check.cpp)

# Test target
add_executable(
    test_list
    test/test_list.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    test_list PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    test_list PRIVATE
    gtest gtest_main
)

if (MSVC)
    target_compile_options(
        vector PRIVATE
        /W4
    )
    target_compile_options(
        test_list PRIVATE
        /W4
    )
else ()
    target_compile_options(
        vector PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        test_list PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS vector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})



















