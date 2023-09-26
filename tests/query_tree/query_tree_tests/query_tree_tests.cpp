#include "jymbo_types.hpp"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE( "query_tree_instantiation", "[QueryTree]" )
{
   jymbo::types::queryNode_t q_node;
   q_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
   q_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::QueryTree q_tree(q_node);
   REQUIRE( true );
}
