#ifndef DERIVATIVE_NODE_HEADER
#define DERIVATIVE_NODE_HEADER

#include "jymbo_types.hpp"

namespace jymbo
{
   jymbo::types::derivativeNode_t initializeOperatorDerivativeNode(
      const jymbo::types::enumOperatorType_t op
   );

   jymbo::types::derivativeNode_t initializeSymbolDerivativeNode(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );

   jymbo::types::derivativeNode_t initializeSymbolDerivativeNode(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );

   jymbo::types::derivativeNode_t initializeReferenceDerivativeNode(
      const int query_node_id
   );
}

#endif
