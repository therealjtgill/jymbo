#include "operators.hpp"

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
      (void)d_node_id;
      (void)q_tree;
      (void)d_tree;
      return {{-1, -1}};
   }

}
