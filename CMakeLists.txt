cmake_minimum_required( VERSION 3.16 )

set(CMAKE_CXX_STANDARD 11)


project(
   JYMBO
   VERSION 0.0.1
)

enable_testing()

include( ${CMAKE_SOURCE_DIR}/cmake/functions.cmake )

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_subdirectory( graph )
add_subdirectory( jymbo )
add_subdirectory( tests )
