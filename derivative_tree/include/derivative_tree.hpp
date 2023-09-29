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

   struct copyFrontierNode_t
   {
      // The ID of a node on a source tree being added as a child to a
      // destination tree's parent node ID.
      int srcNodeId;

      // The ID of a node on a destination tree that is adopting the node
      // from the source tree.
      int destParentNodeId;
   };

   void print(const jymbo::types::DerivativeTree & d_tree);

   std::string queryNodeToString(const jymbo::types::queryNode_t & q_node);

   void derivatize(
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   );

   // Copies a subtree from src_q_tree to dest_q_tree. The subtree from the
   // input tree starting at node ID 'src_node_id' is copied to the location
   // 'dest_node_id' on the output tree.
   void copyQTreeToQTree(
      const int src_node_id,
      const int dest_node_id,
      const jymbo::types::QueryTree & src_q_tree,
      jymbo::types::QueryTree & dest_q_tree
   );

   jymbo::types::queryNode_t convertDNodeToQNode(
      const jymbo::types::derivativeNode_t d_node
   );

   void convertToQTree(
      const jymbo::types::DerivativeTree & d_tree,
      const jymbo::types::QueryTree & q_tree_in,
      jymbo::types::QueryTree & q_tree_out
   );
}

#endif
