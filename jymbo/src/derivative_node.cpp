#include "derivative_node.hpp"

#include "symbols.hpp"

namespace jymbo
{
   jymbo::types::derivativeNode_t initializeOperatorDerivativeNode(
      const jymbo::types::enumOperatorType_t op
   )
   {
      jymbo::types::derivativeNode_t op_node;
      op_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
      op_node.op = op;

      return op_node;
   }

   jymbo::types::derivativeNode_t initializeSymbolDerivativeNode(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::derivativeNode_t op_node;
      op_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kSymbol;
      op_node.symbol = initializeSymbol(
         name, uid, val, symbol_type
      );

      return op_node;
   }

   jymbo::types::derivativeNode_t initializeSymbolDerivativeNode(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::derivativeNode_t op_node;
      op_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kSymbol;
      op_node.symbol = initializeSymbol(
         name, suffix, uid, val, symbol_type
      );

      return op_node;
   }

   jymbo::types::derivativeNode_t initializeReferenceDerivativeNode(
      const int query_node_id
   )
   {
      jymbo::types::derivativeNode_t op_node;
      op_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kReference;
      op_node.qNodeId = query_node_id;

      return op_node;
   }
}
