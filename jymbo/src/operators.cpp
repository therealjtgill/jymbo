#include "derivative_node.hpp"
#include "operators.hpp"
#include "symbols.hpp"

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

   jymbo::types::derivativeFrontierNodes trivialDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      const auto & q_node = q_tree[d_tree[d_node_id].qNodeId];

      auto & d_node = d_tree[d_node_id];
      d_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kSymbol;

      switch(q_node.symbol.symbolType)
      {
         case jymbo::types::enumSymbolType_t::kDependent:
            d_node.symbol = jymbo::initializeSymbol(
               "y'", 0, 0.f, jymbo::types::enumSymbolType_t::kDependent
            );
            break;
         case jymbo::types::enumSymbolType_t::kConstant:
         case jymbo::types::enumSymbolType_t::kParameter:
            d_node.symbol = jymbo::initializeSymbol(
               "0", -1, 0.f, jymbo::types::enumSymbolType_t::kConstant
            );
            break;
         case jymbo::types::enumSymbolType_t::kNull:
            d_node.symbol = jymbo::initializeSymbol(
               "NULL", -1, 0.f, jymbo::types::enumSymbolType_t::kNull
            );
            break;
         case jymbo::types::enumSymbolType_t::kIndependent:
            d_node.symbol = jymbo::initializeSymbol(
               "1", 1, 0.f, jymbo::types::enumSymbolType_t::kConstant
            );
            break;
      }

      return {{-1, -1}};
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

      jymbo::types::derivativeNode_t add_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kAddition
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = add_op;

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
      jymbo::types::derivativeNode_t subtract_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kSubtraction
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = subtract_op;

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
      jymbo::types::derivativeNode_t add_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kAddition
      );

      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = add_op;

      const int left_mult_id = d_tree.addChild(d_node_id, mult_op);
      const int left_frontier_node_id = d_tree.addChild(left_mult_id, left_q_ref);
      d_tree.addChild(left_mult_id, right_q_ref);

      const int right_mult_id = d_tree.addChild(d_node_id, mult_op);
      d_tree.addChild(right_mult_id, left_q_ref);
      const int right_frontier_node_id = d_tree.addChild(right_mult_id, right_q_ref);

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
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t subtract_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kSubtraction
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = subtract_op;

      const int left_mult_op_id = d_tree.addChild(d_node_id, mult_op);
      const int right_mult_op_id = d_tree.addChild(d_node_id, mult_op);

      jymbo::types::derivativeNode_t pow_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kPower
      );

      const int left_frontier_node_id = d_tree.addChild(left_mult_op_id, left_q_ref);
      const int left_pow_op_id = d_tree.addChild(left_mult_op_id, pow_op);

      jymbo::types::derivativeNode_t neg_1_const = jymbo::initializeSymbolDerivativeNode(
         "-1", -1, -1.f, jymbo::types::enumSymbolType_t::kConstant
      );

      jymbo::types::derivativeNode_t neg_2_const = jymbo::initializeSymbolDerivativeNode(
         "-2", -2, -2.f, jymbo::types::enumSymbolType_t::kConstant
      );

      d_tree.addChild(left_pow_op_id, right_q_ref);
      d_tree.addChild(left_pow_op_id, neg_1_const);

      d_tree.addChild(right_mult_op_id, left_q_ref);
      const int second_right_mult_op_id = d_tree.addChild(right_mult_op_id, mult_op);
      const int second_pow_op_id = d_tree.addChild(second_right_mult_op_id, pow_op);
      d_tree.addChild(second_pow_op_id, left_q_ref);
      d_tree.addChild(second_pow_op_id, neg_2_const);

      const int right_frontier_node_id = d_tree.addChild(right_mult_op_id, left_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         {
            left_frontier_node_id,
            right_frontier_node_id
         }
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes powerDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t subtract_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kSubtraction
      );

      jymbo::types::derivativeNode_t pow_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kPower
      );

      jymbo::types::derivativeNode_t ln_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kNaturalLog
      );

      jymbo::types::derivativeNode_t add_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kAddition
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      // d_tree[d_node_id] = mult_op;

      d_tree[d_node_id] = add_op;

      const int top_left_mult_id = d_tree.addChild(d_node_id, mult_op);
      const int top_right_mult_id = d_tree.addChild(d_node_id, mult_op);

      const int right_frontier_node_id = d_tree.addChild(top_left_mult_id, right_q_ref);
      const int left_left_mult_id = d_tree.addChild(top_left_mult_id, mult_op);

      const int pow_id = d_tree.addChild(left_left_mult_id, pow_op);
      const int ln_id = d_tree.addChild(left_left_mult_id, ln_op);

      d_tree.addChild(pow_id, left_q_ref);
      d_tree.addChild(pow_id, right_q_ref);

      const jymbo::types::derivativeNode_t null_sym = \
         jymbo::initializeSymbolDerivativeNode(
            "null", -1, -1.f, jymbo::types::enumSymbolType_t::kNull
         );

      d_tree.addChild(ln_id, left_q_ref);
      d_tree.addChild(ln_id, null_sym);

      const int right_left_mult_id = d_tree.addChild(top_right_mult_id, mult_op);
      const int left_frontier_node_id = d_tree.addChild(top_right_mult_id, left_q_ref);

      d_tree.addChild(right_left_mult_id, right_q_ref);
      const int pow_node_id = d_tree.addChild(right_left_mult_id, pow_op);

      d_tree.addChild(pow_node_id, left_q_ref);
      const int subtract_node_id = d_tree.addChild(pow_node_id, subtract_op);

      jymbo::types::derivativeNode_t pos_1_const = jymbo::initializeSymbolDerivativeNode(
         "1", 1, 1.f, jymbo::types::enumSymbolType_t::kConstant
      );

      d_tree.addChild(subtract_node_id, right_q_ref);
      d_tree.addChild(subtract_node_id, pos_1_const);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         {
            left_frontier_node_id,
            -1
         }
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes sineDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t cos_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kCosine
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = mult_op;

      const int cos_node_id = d_tree.addChild(d_node_id, cos_op);
      const int left_frontier_node_id = d_tree.addChild(d_node_id, left_q_ref);

      d_tree.addChild(cos_node_id, left_q_ref);
      d_tree.addChild(cos_node_id, right_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         left_frontier_node_id,
         -1
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes cosineDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t sin_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kSine
      );

      jymbo::types::derivativeNode_t neg_1_const = jymbo::initializeSymbolDerivativeNode(
         "-1", -1, -1.f, jymbo::types::enumSymbolType_t::kConstant
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = mult_op;

      const int left_mult_id = d_tree.addChild(d_node_id, mult_op);
      const int left_frontier_node_id = d_tree.addChild(d_node_id, left_q_ref);

      d_tree.addChild(left_mult_id, neg_1_const);
      const int sin_id = d_tree.addChild(left_mult_id, sin_op);

      d_tree.addChild(sin_id, left_q_ref);
      d_tree.addChild(sin_id, right_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         left_frontier_node_id,
         -1
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes tangentDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t pow_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kPower
      );

      jymbo::types::derivativeNode_t cos_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kCosine
      );

      jymbo::types::derivativeNode_t neg_2_const = jymbo::initializeSymbolDerivativeNode(
         "-2", -2, -2.f, jymbo::types::enumSymbolType_t::kConstant
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = mult_op;

      const int pow_op_id = d_tree.addChild(d_node_id, pow_op);
      const int left_frontier_node_id = d_tree.addChild(d_node_id, left_q_ref);

      const int cos_op_id = d_tree.addChild(pow_op_id, cos_op);
      d_tree.addChild(pow_op_id, neg_2_const);

      d_tree.addChild(cos_op_id, left_q_ref);
      d_tree.addChild(cos_op_id, right_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         left_frontier_node_id,
         -1
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes naturalLogDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t pow_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kPower
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      d_tree[d_node_id] = mult_op;

      const int pow_op_id = d_tree.addChild(d_node_id, pow_op);
      const int left_frontier_node_id = d_tree.addChild(d_node_id, left_q_ref);

      jymbo::types::derivativeNode_t neg_1_const = \
         jymbo::initializeSymbolDerivativeNode(
            "-1", -1, -1.f, jymbo::types::enumSymbolType_t::kConstant
         );

      d_tree.addChild(pow_op_id, left_q_ref);
      d_tree.addChild(pow_op_id, neg_1_const);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         left_frontier_node_id,
         -1
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes naturalExponentDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      jymbo::types::derivativeNode_t mult_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kMultiplication
      );

      jymbo::types::derivativeNode_t exp_op = jymbo::initializeOperatorDerivativeNode(
         jymbo::types::enumOperatorType_t::kNaturalExponent
      );

      if (d_tree[d_node_id].nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
      {
         std::cout << "Derivative tree at node id " << d_node_id << " should reference the q-tree, but it doesn't\n";
         return {{-1, -1}};
      }

      const auto & q_node_ref = q_tree.getNode(d_tree[d_node_id].qNodeId);

      const int q_left_child_id = q_node_ref.childNodeIds[0];
      const int q_right_child_id = q_node_ref.childNodeIds[1];

      if (q_left_child_id == -1 || q_right_child_id == -1)
      {
         return {{-1, -1}};
      }

      jymbo::types::derivativeNode_t left_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_left_child_id);

      jymbo::types::derivativeNode_t right_q_ref = \
         jymbo::initializeReferenceDerivativeNode(q_right_child_id);

      d_tree[d_node_id] = mult_op;

      // Assumes that the right Q tree reference is null
      const int exp_id = d_tree.addChild(d_node_id, exp_op);
      const int left_frontier_node_id = d_tree.addChild(d_node_id, left_q_ref);

      d_tree.addChild(exp_id, left_q_ref);
      d_tree.addChild(exp_id, right_q_ref);

      jymbo::types::derivativeFrontierNodes d_frontier = {
         left_frontier_node_id,
         -1
      };

      return d_frontier;
   }

   jymbo::types::derivativeFrontierNodes Derivatizer::operator()(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   ) const
   {
      const int q_node_id = d_tree[d_node_id].qNodeId;

      const auto q_node = q_tree[q_node_id];

      switch(q_node.nodeType)
      {
         case jymbo::types::enumQueryNodeType_t::kOperator:
            return operator_derivatives_.at(q_node.op)(
               d_node_id, q_tree, d_tree
            );
         case jymbo::types::enumQueryNodeType_t::kSymbol:
            return trivialDerivativeSubtree(
               d_node_id, q_tree, d_tree
            );
      }


      return {{-1,-1}};
   }
}
