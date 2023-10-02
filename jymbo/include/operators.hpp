#ifndef OPERATORS_HEADER
#define OPERATORS_HEADER

#include "jymbo_types.hpp"

#include <string>
#include <map>

namespace jymbo
{
   std::string operatorToString(const types::enumOperatorType_t op);

   // For taking the derivatives of all symbol types.
   jymbo::types::derivativeFrontierNodes trivialDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes additionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes subtractionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes multiplicationDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes divisionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes powerDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes sineDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes cosineDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes tangentDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes naturalLogDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::derivativeFrontierNodes naturalExponentDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   class Derivatizer
   {
      public:
         jymbo::types::derivativeFrontierNodes operator()(
            const int d_node_id,
            const jymbo::types::QueryTree & q_tree,
            jymbo::types::DerivativeTree & d_tree
         ) const;

      private:
         typedef jymbo::types::derivativeFrontierNodes (*op_derivative_fn)(
            const int,
            const jymbo::types::QueryTree &,
            jymbo::types::DerivativeTree &
         );

         const std::map<
            jymbo::types::enumOperatorType_t,
            op_derivative_fn
         > operator_derivatives_ = {
            {jymbo::types::enumOperatorType_t::kAddition, additionDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kSubtraction, subtractionDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kMultiplication, multiplicationDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kDivision, divisionDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kPower, powerDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kSine, sineDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kCosine, cosineDerivativeSubtree},
            {jymbo::types::enumOperatorType_t::kTangent, tangentDerivativeSubtree}
         };
   };
}

#endif
