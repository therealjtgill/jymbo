#ifndef SYMBOL_TYPES_HEADER
#define SYMBOL_TYPES_HEADER

namespace jymbo
{

namespace types
{

   enum class enumSymbolType_t
   {
      kDependent = 0,
      kIndependent = 1,
      kParameter = 2,
      kConstant = 3
   };

   struct symbol_t
   {
      char name[16];
      int uid;
      float val;
      enumSymbolType_t symbolType;
   };

}

}

#endif
