#include "polynomial_query_tree.hpp"

#include <algorithm>
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
      std::snprintf(an_sym_node.symbol.name, 16, "a%i", n);
      an_sym_node.symbol.uid = 2 * n + 5;
      an_sym_node.symbol.val = 0.f;
      an_sym_node.symbol.symbolType = jymbo::types::enumSymbolType_t::kParameter;

      jymbo::types::queryNode_t n_sym_node;
      n_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      std::snprintf(n_sym_node.symbol.name, 16, "%i", n);
      n_sym_node.symbol.uid = 3 * n + 5;
      n_sym_node.symbol.val = static_cast<float>(n);
      n_sym_node.symbol.symbolType = jymbo::types::enumSymbolType_t::kParameter;

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
      std::snprintf(q_y_node.symbol.name, 16, "y");
      q_y_node.symbol.symbolType = jymbo::types::enumSymbolType_t::kDependent;
      q_y_node.symbol.uid = 0;
      q_y_node.symbol.val = 0.f;

      jymbo::types::queryNode_t plus_op_node;
      plus_op_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      plus_op_node.op = jymbo::types::enumOperatorType_t::kAddition;

      q_tree.addChild(q_tree.getRootId(), q_y_node);

      int plus_node_id = q_tree.addChild(q_tree.getRootId(), plus_op_node);

      jymbo::types::queryNode_t x_sym_node;
      x_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      std::snprintf(x_sym_node.symbol.name, 16, "x");
      x_sym_node.symbol.uid = 1;
      x_sym_node.symbol.val = 0.f;
      x_sym_node.symbol.symbolType = jymbo::types::enumSymbolType_t::kIndependent;

      jymbo::types::queryNode_t a0_sym_node;
      a0_sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      std::snprintf(a0_sym_node.symbol.name, 16, "a0");
      a0_sym_node.symbol.uid = 1;
      a0_sym_node.symbol.val = 0.f;
      a0_sym_node.symbol.symbolType = jymbo::types::enumSymbolType_t::kParameter;

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
