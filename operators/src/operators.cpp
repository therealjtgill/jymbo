#include "operators.hpp"

#include <iostream>

namespace jymbo
{

   std::string operatorToString(const types::enumOperatorType_t op)
   {
      switch(op)
      {
         case jymbo::types::enumOperatorType_t::kEqual:
            return std::string("equal");
            break;
         case jymbo::types::enumOperatorType_t::kAddition:
            return std::string("add");
            break;
         case jymbo::types::enumOperatorType_t::kSubtraction:
            return std::string("subtract");
            break;
         case jymbo::types::enumOperatorType_t::kMultiplication:
            return std::string("mult");
            break;
         case jymbo::types::enumOperatorType_t::kDivision:
            return std::string("divide");
            break;
         case jymbo::types::enumOperatorType_t::kNaturalLog:
            return std::string("ln");
            break;
         case jymbo::types::enumOperatorType_t::kNaturalExponent:
            return std::string("exp");
            break;
         case jymbo::types::enumOperatorType_t::kSine:
            return std::string("sin");
            break;
         case jymbo::types::enumOperatorType_t::kCosine:
            return std::string("cos");
            break;
         case jymbo::types::enumOperatorType_t::kTangent:
            return std::string("tan");
            break;
         case jymbo::types::enumOperatorType_t::kPower:
            return std::string("pow");
            break;
      }

      return std::string("no-operation-found");
   }

   jymbo::types::derivativeFrontierNodes additionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      // Ok, so the operator referenced by d_node_id in the d_tree is addition.
      // This means that I need to replace the node at d_node_id with nodes
      // that are equivalent to the derivative of the addition operator.

      jymbo::types::derivativeNode_t add_op;
      add_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      add_op.op = jymbo::types::enumOperatorType_t::kAddition;

      if (d_tree[d_node_id].node_type != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].q_node_id);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      d_tree[d_node_id] = add_op;

      jymbo::types::derivativeNode_t left_q_ref;
      left_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      left_q_ref.q_node_id = q_left_child_id;

      jymbo::types::derivativeNode_t right_q_ref;
      right_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      right_q_ref.q_node_id = q_right_child_id;

      jymbo::types::derivativeFrontierNodes d_frontier = {
         {
            d_tree.addChild(d_node_id, left_q_ref),
            d_tree.addChild(d_node_id, right_q_ref),
         }
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes subtractionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t subtract_op;
      subtract_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      subtract_op.op = jymbo::types::enumOperatorType_t::kSubtraction;

      if (d_tree[d_node_id].node_type != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].q_node_id);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      d_tree[d_node_id] = subtract_op;

      jymbo::types::derivativeNode_t left_q_ref;
      left_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      left_q_ref.q_node_id = q_left_child_id;

      jymbo::types::derivativeNode_t right_q_ref;
      right_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      right_q_ref.q_node_id = q_right_child_id;

      jymbo::types::derivativeFrontierNodes d_frontier = {
         {
            d_tree.addChild(d_node_id, left_q_ref),
            d_tree.addChild(d_node_id, right_q_ref),
         }
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes multiplicationDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t add_op;
      add_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      add_op.op = jymbo::types::enumOperatorType_t::kAddition;

      jymbo::types::derivativeNode_t mult_op;
      mult_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      mult_op.op = jymbo::types::enumOperatorType_t::kMultiplication;

      if (d_tree[d_node_id].node_type != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].q_node_id);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      d_tree[d_node_id] = add_op;

      jymbo::types::derivativeNode_t left_q_ref;
      left_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      left_q_ref.q_node_id = q_left_child_id;

      jymbo::types::derivativeNode_t right_q_ref;
      right_q_ref.node_type = jymbo::types::enumDerivativeNodeType_t::kReference;
      right_q_ref.q_node_id = q_right_child_id;

      const int left_mult_id = d_tree.addChild(d_node_id, mult_op);
      const int left_frontier_node_id = d_tree.addChild(left_mult_id, left_q_ref);
      d_tree.addChild(left_mult_id, right_q_ref);

      const int right_mult_id = d_tree.addChild(d_node_id, mult_op);
      d_tree.addChild(right_mult_id, left_q_ref);
      const int right_frontier_node_id = d_tree.addChild(left_mult_id, right_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         {
            left_frontier_node_id,
            right_frontier_node_id
         }
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes divisionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op;
      mult_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      mult_op.op = jymbo::types::enumOperatorType_t::kMultiplication;

      jymbo::types::derivativeNode_t subtract_op;
      subtract_op.node_type = jymbo::types::enumDerivativeNodeType_t::kOperator;
      subtract_op.op = jymbo::types::enumOperatorType_t::kSubtraction;

      if (d_tree[d_node_id].node_type != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      static_assert(false);
   }

   jymbo::types::derivativeFrontierNodes powerDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      static_assert(false);
   }

}
