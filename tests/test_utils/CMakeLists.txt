set(
   headers
   polynomial_query_tree.hpp
)

set(
   sources
   polynomial_query_tree.cpp
)

set(
   target
   jymbotestutils
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_library(
   ${target}
   SHARED
   ${sources}
   ${headers}
)

target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-function -Werror)

target_include_directories(
   ${target}
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
   ${target}
   PROPERTIES
   LINKER_LANGUAGE
   CXX
)

target_link_libraries(
   ${target}
   jymbotypes
)
