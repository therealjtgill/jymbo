cmake_minimum_required( VERSION 3.16 )

set(CMAKE_CXX_STANDARD 11)

project(
   JYMBO
   VERSION 0.0.1
)

add_subdirectory( graph )
add_subdirectory( operators )
add_subdirectory( symbols )
add_subdirectory( tests )
