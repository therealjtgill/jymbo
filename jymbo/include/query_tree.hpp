#ifndef QUERY_TREE_HEADER
#define QUERY_TREE_HEADER

#include "jymbo_types.hpp"
#include "operators.hpp"

namespace query_tree
{
   struct printFrontierNode_t
   {
      // The node's ID in the tree.
      int nodeId;

      // Parentheses count
      int parenthesesCount;

      // The node's child ID - for a binary tree this is:
      //    0: left child
      //    1: right child
      int childId;
   };

   void print(const jymbo::types::QueryTree & q_tree);
}

#endif
