#ifndef SYMBOLS_HEADER
#define SYMBOLS_HEADER

#include "jymbo_types.hpp"

namespace jymbo
{
   jymbo::types::symbol_t initializeSymbol(
      const char * name,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );

   jymbo::types::symbol_t initializeSymbol(
      const char * name,
      const int suffix,
      const int uid,
      const float val,
      const jymbo::types::enumSymbolType_t symbol_type
   );
}

#endif
