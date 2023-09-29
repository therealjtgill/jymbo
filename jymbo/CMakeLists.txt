set(
   headers
   include/derivative_tree.hpp
   include/jymbo_types.hpp
   include/operators.hpp
   include/query_tree.hpp
   include/symbols.hpp
)

set(
   sources
   src/derivative_tree.cpp
   src/operators.cpp
   src/query_tree.cpp
   src/symbols.cpp
)

set(
   target
   jymbo
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

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
   ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(
   ${target}
   PROPERTIES
   LINKER_LANGUAGE
   CXX
)

target_link_libraries(
   ${target}
   edbdgraph
)
