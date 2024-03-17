cmake_minimum_required(VERSION 3.13)

project(git-starter-cpp
        LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23) # Enable the C++20 standard
# set(CMAKE_CXX_STANDSARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(SOURCE_FILES src/Server.cpp)

add_executable(server ${SOURCE_FILES})
target_link_libraries(server -lz)
