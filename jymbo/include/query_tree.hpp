#ifndef QUERY_TREE_HEADER
#define QUERY_TREE_HEADER

#include "jymbo_types.hpp"
#include "operators.hpp"

#include <iostream>
#include <string>

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

   void print(const jymbo::types::QueryTree & q_tree)
   {
      std::string out_string;
      std::vector<printFrontierNode_t> frontier;

      frontier.reserve(q_tree.size());

      const int root_node_id = q_tree.getRootId();

      printFrontierNode_t root_frontier_node;
      root_frontier_node.childId = 0;
      root_frontier_node.parenthesesCount = 0;
      root_frontier_node.nodeId = root_node_id;

      frontier.push_back(root_frontier_node);

      while (!frontier.empty())
      {
         const printFrontierNode_t frontier_node = frontier.back();
         frontier.pop_back();

         const jymbo::types::QueryTree::MetaNode_T & tree_node = \
            q_tree.getNode(frontier_node.nodeId);

         if (frontier_node.childId == 1)
         {
            out_string += std::string(",");
         }

         if (tree_node.meta.nodeType == jymbo::types::enumQueryNodeType_t::kOperator)
         {
            out_string += jymbo::operatorToString(tree_node.meta.op);
            out_string += std::string("(");
         }
         else if (tree_node.meta.nodeType == jymbo::types::enumQueryNodeType_t::kSymbol)
         {
            out_string += std::string(tree_node.meta.symbol.name);
         }

         if (tree_node.childNodeIds[0] == -1 || tree_node.childNodeIds[1] == -1)
         {
            if (frontier_node.childId == 1)
            {
               for (int i = 0; i < frontier_node.parenthesesCount; ++i)
               {
                  out_string += std::string(")");
               }
            }
            continue;
         }

         printFrontierNode_t left_frontier_node;
         left_frontier_node.childId = 0;
         left_frontier_node.parenthesesCount = 0;
         left_frontier_node.nodeId = tree_node.childNodeIds[0];

         printFrontierNode_t right_frontier_node;
         right_frontier_node.childId = 1;
         right_frontier_node.parenthesesCount = frontier_node.parenthesesCount + 1;
         right_frontier_node.nodeId = tree_node.childNodeIds[1];

         frontier.push_back(right_frontier_node);
         frontier.push_back(left_frontier_node);
      }

      std::cout << out_string << "\n";
   }
}

#endif
