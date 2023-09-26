cmake_minimum_required( VERSION 3.16 )

set(CMAKE_CXX_STANDARD 11)

project(
   JYMBO
   VERSION 0.0.1
)

enable_testing()

include( ${CMAKE_SOURCE_DIR}/cmake/functions.cmake )

add_subdirectory( graph )
add_subdirectory( operators )
add_subdirectory( query_tree )
add_subdirectory( symbols )
add_subdirectory( tests )
add_subdirectory( types )
