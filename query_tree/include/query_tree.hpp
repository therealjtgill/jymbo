#ifndef QUERY_TREE_HEADER
#define QUERY_TREE_HEADER

#include "jymbo_types.hpp"
#include <iostream>

namespace query_tree
{
   struct printFrontierNode_t
   {
      // The node's ID in the tree.
      int nodeId;

      // The depth of the node in the tree.
      int depth;

      // The node's child ID - for a binary tree this is:
      //    0: left child
      //    1: right child
      int childId;
   };

   void print(const jymbo::types::QueryTree & q_tree)
   {
      std::vector<printFrontierNode_t> frontier;

      frontier.reserve(q_tree.size());

      const int root_node_id = q_tree.getRootId();

      printFrontierNode_t root_frontier_node;
      root_frontier_node.childId = 0;
      root_frontier_node.depth = 0;
      root_frontier_node.nodeId = root_node_id;

      while (!frontier.empty())
      {
         const printFrontierNode_t frontier_node = frontier.back();
         frontier.pop_back();

         const jymbo::types::QueryTree::MetaNode_T & tree_node = \
            q_tree.getNode(frontier_node.nodeId);

         printFrontierNode_t left_frontier_node;
         left_frontier_node.childId = 0;
         left_frontier_node.depth = frontier_node.depth + 1;
         left_frontier_node.nodeId = tree_node.childNodeIds[0];

         printFrontierNode_t right_frontier_node;
         right_frontier_node.childId = 1;
         right_frontier_node.depth = frontier_node.depth + 1;
         right_frontier_node.nodeId = tree_node.childNodeIds[1];

         frontier.push_back(right_frontier_node);
         frontier.push_back(left_frontier_node);
      }
   }
}

#endif
