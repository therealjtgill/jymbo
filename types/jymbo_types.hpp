#include "nary_tree.hpp"

namespace jymbo
{

namespace types
{

   enum class enumOperatorType_t
   {
      kEqual = 0,
      kAddition = 1,
      kSubtraction = 2,
      kMultiplication = 3,
      kDivision = 4,
      kNaturalLog = 5,
      kNaturalExponent = 6,
      kSine = 7,
      kCosine = 8,
      kTangent = 9,
      kPower = 10,
      kExponentiation = 11,
   };

   enum class enumSymbolType_t
   {
      kDependent = 0,
      kIndependent = 1,
      kParameter = 2,
      kConstant = 3
   };

   enum class enumDerivativeNodeType_t
   {
      kSymbol = 0,
      kOperator = 1,
      kReference = 2,
   };

   enum class enumQueryNodeType_t
   {
      kSymbol = 0,
      kOperator = 1,
   };

   struct symbol_t
   {
      char name[16];
      int uid;
      float val;
      enumSymbolType_t symbolType;
   };

   struct queryNode_t
   {
      union
      {
         symbol_t symbol;
         enumOperatorType_t op;
      };

      enumQueryNodeType_t nodeType;
   };

   struct derivativeNode_t
   {
      union
      {
         symbol_t symbol;
         enumOperatorType_t op;
         int q_node_id;
      };

      enumDerivativeNodeType_t node_type;
   };

}

}
