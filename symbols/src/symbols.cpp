#include "symbols.hpp"

#include <cstdio>

namespace jymbo
{
   jymbo::types::symbol_t initializeSymbol(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::symbol_t temp_symbol;
      std::snprintf(temp_symbol.name, 16, "%s", name);
      temp_symbol.symbolType = symbol_type;
      temp_symbol.uid = uid;
      temp_symbol.val = val;

      return temp_symbol;
   }

   jymbo::types::symbol_t initializeSymbol(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   )
   {
      jymbo::types::symbol_t temp_symbol;
      std::snprintf(temp_symbol.name, 16, "%s%i", name, suffix);
      temp_symbol.symbolType = symbol_type;
      temp_symbol.uid = uid;
      temp_symbol.val = val;

      return temp_symbol;
   }
}
