#include "query_node.hpp"
#include "symbols.hpp"

namespace jymbo
{
   jymbo::types::queryNode_t initializeOperatorQueryNode(
      const jymbo::types::enumOperatorType_t op
   )
   {
      jymbo::types::queryNode_t op_node;
      op_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
      op_node.op = op;

      return op_node;
   }

   jymbo::types::queryNode_t initializeSymbolQueryNode(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::queryNode_t sym_node;
      sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      sym_node.symbol = initializeSymbol(
         name, uid, val, symbol_type
      );

      return sym_node;
   }

   jymbo::types::queryNode_t initializeSymbolQueryNode(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::queryNode_t sym_node;
      sym_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
      sym_node.symbol = initializeSymbol(
         name, suffix, uid, val, symbol_type
      );

      return sym_node;
   }
}
