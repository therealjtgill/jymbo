#ifndef DERIVATIVE_TREE_HEADER
#define DERIVATIVE_TREE_HEADER

#include "jymbo_types.hpp"

#include <iostream>
#include <string>

namespace derivative_tree
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

   void print(const jymbo::types::DerivativeTree & d_tree);

   std::string queryNodeToString(const jymbo::types::queryNode_t & q_node);

   void derivatize(
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   jymbo::types::queryNode_t convertDNodeToQNode(
      const jymbo::types::derivativeNode_t d_node,
      const jymbo::types::QueryTree & q_tree_in
   );

   void convertToQTree(
      const jymbo::types::DerivativeTree & d_tree,
      const jymbo::types::QueryTree & q_tree_in,
      jymbo::types::QueryTree & q_tree_out
   );
}

#endif
