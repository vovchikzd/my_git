cmake_minimum_required(VERSION 3.13)

project(git-starter-cpp
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Enable the C++20 standard
# set(CMAKE_CXX_STANDSARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

if((CMAKE_GENERATOR STREQUAL "Ninja")
   AND (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24))
  set(CMAKE_COLOR_DIAGNOSTICS On) 
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

set(SOURCE_FILES src/Server.cpp)

add_executable(server ${SOURCE_FILES})

add_subdirectory(zstr)
target_link_libraries(server zstr::zstr)
# target_link_libraries(server -lz)
