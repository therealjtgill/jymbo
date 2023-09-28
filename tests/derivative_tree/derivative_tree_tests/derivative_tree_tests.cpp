#include "jymbo_types.hpp"
#include "derivative_tree.hpp"
#include "polynomial_query_tree.hpp"
#include "query_tree.hpp"
#include "symbols.hpp"

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE( "derivative_tree_instantiation", "[DerivativeTree]" )
{
   jymbo::types::derivativeNode_t d_node;
   d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);
   REQUIRE( true );
}

TEST_CASE( "print derivative tree", "[DerivativeTree]" )
{
   jymbo::types::derivativeNode_t d_node;
   d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);

   jymbo::types::derivativeNode_t d_y_node;
   d_y_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kSymbol;
   d_y_node.symbol = jymbo::initializeSymbol(
      "y", 0, 0.f, jymbo::types::enumSymbolType_t::kDependent
   );

   jymbo::types::derivativeNode_t divide_op;
   divide_op.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   divide_op.op = jymbo::types::enumOperatorType_t::kDivision;

   jymbo::types::derivativeNode_t left_query_ref;
   left_query_ref.nodeType = jymbo::types::enumDerivativeNodeType_t::kReference;
   left_query_ref.qNodeId = 0;

   jymbo::types::derivativeNode_t right_query_ref;
   right_query_ref.nodeType = jymbo::types::enumDerivativeNodeType_t::kReference;
   right_query_ref.qNodeId = 1;

   d_tree.addChild(d_tree.getRootId(), d_y_node);
   const int divide_op_id = d_tree.addChild(d_tree.getRootId(), divide_op);
   d_tree.addChild(divide_op_id, left_query_ref);
   d_tree.addChild(divide_op_id, right_query_ref);

   derivative_tree::print(d_tree);
}

TEST_CASE( "take derivative of multiplication", "[DerivativeTree]" )
{
   jymbo::types::queryNode_t q_node;
   q_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
   q_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::QueryTree q_tree(q_node);

   jymbo::types::queryNode_t q_y_node;
   q_y_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
   q_y_node.symbol = jymbo::initializeSymbol(
      "y", 0, 0.f, jymbo::types::enumSymbolType_t::kDependent
   );

   jymbo::types::queryNode_t mult_op;
   mult_op.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
   mult_op.op = jymbo::types::enumOperatorType_t::kMultiplication;

   jymbo::types::queryNode_t q_x_node;
   q_x_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
   q_x_node.symbol = jymbo::initializeSymbol(
      "x", 0, 0.f, jymbo::types::enumSymbolType_t::kIndependent
   );

   jymbo::types::queryNode_t q_a_node;
   q_a_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
   q_a_node.symbol = jymbo::initializeSymbol(
      "a", 0, 0.f, jymbo::types::enumSymbolType_t::kParameter
   );

   q_tree.addChild(q_tree.getRootId(), q_y_node);
   const int mult_id = q_tree.addChild(q_tree.getRootId(), mult_op);
   q_tree.addChild(mult_id, q_x_node);
   q_tree.addChild(mult_id, q_a_node);

   query_tree::print(q_tree);

   jymbo::types::derivativeNode_t d_node;
   d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);

   derivative_tree::derivatize(q_tree, d_tree);

   derivative_tree::print(d_tree);

}

TEST_CASE( "take derivative of linear equation", "[DerivativeTree]" )
{
   jymbo::types::queryNode_t q_node;
   q_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
   q_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::QueryTree q_tree(q_node);

   test_utils::polynomialQueryTree(1, q_tree);

   query_tree::print(q_tree);

   jymbo::types::derivativeNode_t d_node;
   d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);

   derivative_tree::derivatize(q_tree, d_tree);

   derivative_tree::print(d_tree);
}

TEST_CASE( "take derivative of quadratic equation", "[DerivativeTree]" )
{
   jymbo::types::queryNode_t q_node;
   q_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
   q_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::QueryTree q_tree(q_node);

   test_utils::polynomialQueryTree(2, q_tree);

   query_tree::print(q_tree);

   jymbo::types::derivativeNode_t d_node;
   d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
   d_node.op = jymbo::types::enumOperatorType_t::kEqual;
   jymbo::types::DerivativeTree d_tree(d_node);

   derivative_tree::derivatize(q_tree, d_tree);

   derivative_tree::print(d_tree);
}
