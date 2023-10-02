#include "jymbo_types.hpp"

#include "polynomial_query_tree.hpp"
#include "query_node.hpp"
#include "query_tree.hpp"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE( "query_tree_instantiation", "[QueryTree]" )
{
   jymbo::types::queryNode_t q_node = jymbo::initializeOperatorQueryNode(
      jymbo::types::enumOperatorType_t::kEqual
   );

   jymbo::types::QueryTree q_tree(q_node);
   REQUIRE( true );
}

TEST_CASE( "quadratic tree instantiation", "[QueryTree]")
{
   jymbo::types::queryNode_t q_node = jymbo::initializeOperatorQueryNode(
      jymbo::types::enumOperatorType_t::kEqual
   );

   jymbo::types::QueryTree q_tree(q_node);

   test_utils::polynomialQueryTree(2, q_tree);

   query_tree::print(q_tree);

   REQUIRE( true );
}

TEST_CASE( "cubic tree instantiation", "[QueryTree]")
{
   jymbo::types::queryNode_t q_node = jymbo::initializeOperatorQueryNode(
      jymbo::types::enumOperatorType_t::kEqual
   );

   jymbo::types::QueryTree q_tree(q_node);

   test_utils::polynomialQueryTree(3, q_tree);

   query_tree::print(q_tree);

   REQUIRE( true );
}
