#ifndef OPERATORS_HEADER
#define OPERATORS_HEADER

#include "jymbo_types.hpp"

#include <string>

namespace jymbo
{
   std::string operatorToString(const types::enumOperatorType_t op);

   jymbo::types::derivativeFrontierNodes additionDerivativeSubtree(
      const int d_node_id,
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   class Derivatizer
   {

   };
}

#endif
