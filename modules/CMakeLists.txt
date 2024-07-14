cmake_minimum_required(VERSION 3.28)

# add modules
target_sources(mgit PRIVATE
               FILE_SET modules TYPE CXX_MODULES
               FILES
                 # ${CMAKE_CURRENT_SOURCE_DIR}/mgt.cppm
                 ${CMAKE_CURRENT_SOURCE_DIR}/sha1.cppm
)

