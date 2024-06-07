cmake_minimum_required(VERSION 3.13)

project(my_git
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDSARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

if((CMAKE_GENERATOR STREQUAL "Ninja")
   AND (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24))
  set(CMAKE_COLOR_DIAGNOSTICS On) 
endif()

add_compile_options(-Wall -Wextra -Wpedantic)


add_executable(mgit ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(zstr)
target_link_libraries(mgit zstr::zstr)
# target_link_libraries(mgit -lz)
