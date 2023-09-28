#include "derivative_tree.hpp"
#include "operators.hpp"
#include "symbols.hpp"

namespace derivative_tree
{
   
   void print(const jymbo::types::DerivativeTree & d_tree)
   {
      std::string out_string;
      std::vector<printFrontierNode_t> frontier;

      frontier.reserve(d_tree.size());

      const int root_node_id = d_tree.getRootId();

      printFrontierNode_t root_frontier_node;
      root_frontier_node.childId = 0;
      root_frontier_node.parenthesesCount = 0;
      root_frontier_node.nodeId = root_node_id;

      frontier.push_back(root_frontier_node);

      while (!frontier.empty())
      {
         const printFrontierNode_t frontier_node = frontier.back();
         frontier.pop_back();

         const jymbo::types::DerivativeTree::MetaNode_T & tree_node = \
            d_tree.getNode(frontier_node.nodeId);

         if (frontier_node.childId == 1)
         {
            out_string += std::string(",");
         }

         if (tree_node.meta.nodeType == jymbo::types::enumDerivativeNodeType_t::kOperator)
         {
            out_string += jymbo::operatorToString(tree_node.meta.op);
            out_string += std::string("(");
         }
         else if (tree_node.meta.nodeType == jymbo::types::enumDerivativeNodeType_t::kSymbol)
         {
            out_string += std::string(tree_node.meta.symbol.name);
         }
         else if (tree_node.meta.nodeType == jymbo::types::enumDerivativeNodeType_t::kReference)
         {
            out_string += std::string("Q");
            out_string += std::to_string(tree_node.meta.qNodeId);
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

   void derivatize(
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      std::vector<int> frontier;

      frontier.reserve(q_tree.size());

      jymbo::types::derivativeNode_t d_root_node;
      d_root_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kOperator;
      d_root_node.op = jymbo::types::enumOperatorType_t::kEqual;

      jymbo::types::derivativeNode_t d_y_node;
      d_y_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kSymbol;
      d_y_node.symbol = jymbo::initializeSymbol(
         "y'", 0, 0.f, jymbo::types::enumSymbolType_t::kDependent
      );

      jymbo::types::derivativeNode_t rhs_q_ref_node;
      rhs_q_ref_node.nodeType = jymbo::types::enumDerivativeNodeType_t::kReference;
      rhs_q_ref_node.qNodeId = q_tree.getNode(q_tree.getRootId()).childNodeIds[1];

      d_tree.setRoot(d_root_node);
      const int d_root_id = d_tree.getRootId();

      d_tree.addChild(d_root_id, d_y_node);
      const int d_frontier_id = d_tree.addChild(d_root_id, rhs_q_ref_node);

      frontier.push_back(d_frontier_id);

      while(frontier.size() > 0)
      {
         const int d_node_id = frontier.back();
         frontier.pop_back();

         const auto d_node = d_tree[d_node_id];

         if (d_node.nodeType != jymbo::types::enumDerivativeNodeType_t::kReference)
         {
            std::cout << "tried to expand a node that isn't a reference to the q-tree\n";
            return;
         }

         
      }
   }
}
