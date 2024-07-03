cmake_minimum_required(VERSION 3.28)

project(my_git
        LANGUAGES CXX)

# check compilers
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17))
  message(FATAL_ERROR "Requires at least clang 17")
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
       AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14))
  message(FATAL_ERROR "Requires at least gcc 14")
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "MSVS")
       AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.34))
  message(FATAL_ERROR "Requires at least MSVC 19.34")
endif()

# check generators
if(UNIX AND (CMAKE_GENERATOR STREQUAL "Unix Makefiles"))
  message(FATAL_ERROR "\nC++ modules aren't supported by Unix Makefiles."
                      "\nModules are supported by Ninja for v.1.11 and newer.")
elseif((CMAKE_GENERATOR MATCHES "Visual Studio")
       AND (MSVC_TOOLSET_VERSION LESS 143))
  message(FATAL_ERROR "Requires at least Visual Studio 17 2022 generator")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDSARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_COLOR_DIAGNOSTICS On)
add_compile_options(-Wall -Wextra -Wpedantic)

set(PROJECT_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_executable(mgit ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_sources(mgit PUBLIC
                 ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# modules dir
add_subdirectory(${PROJECT_MODULES_DIR})

add_subdirectory(zstr)
target_link_libraries(mgit zstr::zstr)
# target_link_libraries(mgit -lz)
