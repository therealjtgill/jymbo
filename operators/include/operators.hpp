#ifndef OPERATORS_HEADER
#define OPERATORS_HEADER

#include "jymbo_types.hpp"

#include <string>

namespace jymbo
{
   std::string operatorToString(const types::enumOperatorType_t op)
   {
      switch(op)
      {
         case kEqual:
            return std::string("equal");
            break;
         case kAddition:
            return std::string("add");
            break;
         case kSubtraction:
            return std::string("subtract");
            break;
         case kMultiplication:
            return std::string("mult");
            break;
         case kDivision:
            return std::string("divide");
            break;
         case kNaturalLog:
            return std::string("ln");
            break;
         case kNaturalExponent:
            return std::string("exp");
            break;
         case kSine:
            return std::string("sin");
            break;
         case kCosine:
            return std::string("cos");
            break;
         case kTangent:
            return std::string("tan");
            break;
         case kPower:
            return std::string("pow");
            break;
      }

      return std::string("no-operation-found");
   }
}

#endif
