#ifndef QUERY_NODE_HEADER
#define QUERY_NODE_HEADER

#include "jymbo_types.hpp"

namespace jymbo
{
   jymbo::types::queryNode_t initializeOperatorQueryNode(
      const jymbo::types::enumOperatorType_t op
   );

   jymbo::types::queryNode_t initializeSymbolQueryNode(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );

   jymbo::types::queryNode_t initializeSymbolQueryNode(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );
}

#endif
