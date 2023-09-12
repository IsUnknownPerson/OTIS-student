cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
#set(PROJECT_VERSION_PATCH 0.0.${PATCH_VERSION})

#project(helloworld VERSION ${PROJECT_VERSION_PATCH})
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

project(homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

add_executable(homework main.cpp)
add_library(helloworld lib.cpp)
#add_executable(test_version test_version.cpp)



target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(homework PRIVATE helloworld)

install(TARGETS homework
    RUNTIME DESTINATION bin)
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


    set(CPACK_GENERATOR DEB)
#
   set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
  set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
 set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
#
   set(CPACK_PACKAGE_CONTACT example@example.com)
#
    include(CPack)
