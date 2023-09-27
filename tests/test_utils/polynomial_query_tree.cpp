#include "polynomial_query_tree.hpp"
#include "symbols.hpp"

#include <cstdio>
#include <iostream>

namespace test_utils
{
   void addAPowXN(
      const int n,
      int plus_node_id,
      const jymbo::types::queryNode_t & indep_sym_node,
      jymbo::types::QueryTree & q_tree
   )
   {
      jymbo::types::queryNode_t mult_op_node;
      mult_op_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      mult_op_node.op = jymbo::types::enumOperatorType_t::kMultiplication;

      jymbo::types::queryNode_t pow_op_node;
      pow_op_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      pow_op_node.op = jymbo::types::enumOperatorType_t::kPower;

      jymbo::types::queryNode_t an_sym_node;
      an_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      an_sym_node.symbol = jymbo::initializeSymbol(
         "a", n, 2 * n + 5, 0.f, jymbo::types::enumSymbolType_t::kParameter
      );

      jymbo::types::queryNode_t n_sym_node;
      n_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      n_sym_node.symbol = jymbo::initializeSymbol(
         "", n, 3 * n + 5, static_cast<float>(n), jymbo::types::enumSymbolType_t::kParameter
      );

      int mult_node_id = q_tree.addChild(plus_node_id, mult_op_node);
      q_tree.addChild(mult_node_id, an_sym_node);
      int pow_node_id = q_tree.addChild(mult_node_id, pow_op_node);

      q_tree.addChild(pow_node_id, indep_sym_node);
      q_tree.addChild(pow_node_id, n_sym_node);
   }

   void polynomialQueryTree(const int n, jymbo::types::QueryTree & q_tree)
   {
      (void)n;
      jymbo::types::queryNode_t q_root_node;
      q_root_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      q_root_node.op = jymbo::types::enumOperatorType_t::kEqual;

      q_tree.setRoot(q_root_node);

      jymbo::types::queryNode_t q_y_node;
      q_y_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      q_y_node.symbol = jymbo::initializeSymbol(
         "y", 0, 0.f, jymbo::types::enumSymbolType_t::kDependent
      );

      jymbo::types::queryNode_t plus_op_node;
      plus_op_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      plus_op_node.op = jymbo::types::enumOperatorType_t::kAddition;

      q_tree.addChild(q_tree.getRootId(), q_y_node);

      int plus_node_id = q_tree.addChild(q_tree.getRootId(), plus_op_node);

      jymbo::types::queryNode_t x_sym_node;
      x_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      x_sym_node.symbol = jymbo::initializeSymbol(
         "x", 1, 0.f, jymbo::types::enumSymbolType_t::kIndependent
      );

      jymbo::types::queryNode_t a0_sym_node;
      a0_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      a0_sym_node.symbol = jymbo::initializeSymbol(
         "a0", 2, 0.f, jymbo::types::enumSymbolType_t::kParameter
      );

      int counter = n;
      while(counter > 0)
      {
         addAPowXN(counter, plus_node_id, x_sym_node, q_tree);
         plus_node_id = q_tree.addChild(plus_node_id, plus_op_node);

         counter -= 1;
      }

      q_tree[plus_node_id] = a0_sym_node;
   }
}
