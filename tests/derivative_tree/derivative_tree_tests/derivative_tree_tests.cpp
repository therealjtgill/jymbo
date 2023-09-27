#include "jymbo_types.hpp"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE( "derivative_tree_instantiation", "[DerivativeTree]" )
{
   jymbo::types::derivativeNode_t d_node;
   d_node.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);
   REQUIRE( true );
}
