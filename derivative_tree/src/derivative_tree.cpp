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

   std::string queryNodeToString(const jymbo::types::queryNode_t & q_node)
   {
      switch(q_node.nodeType)
      {
         case jymbo::types::enumQueryNodeType_t::kOperator:
            return jymbo::operatorToString(q_node.op);
         case jymbo::types::enumQueryNodeType_t::kSymbol:
            return std::string(q_node.symbol.name);
      }

      return std::string("cannot print query node");
   }

   void derivatize(
      const jymbo::types::QueryTree & q_tree,
      jymbo::types::DerivativeTree & d_tree
   )
   {
      std::vector<int> frontier;

      jymbo::Derivatizer derivatizer;

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

         std::cout << "taking the derivative of query node ID " << d_tree[d_node_id].qNodeId << "\n";
         std::cout << "\twith type: " << queryNodeToString(q_tree[d_node.qNodeId]) << "\n";

         jymbo::types::derivativeFrontierNodes child_nodes = derivatizer(
            d_node_id, q_tree, d_tree
         );

         for (int i = 0; i < 2; ++i)
         {
            if (child_nodes.nodeIdsToDerivatize[i] >= 0)
            {
               frontier.push_back(child_nodes.nodeIdsToDerivatize[i]);
            }
         }
      }
   }

   void copyQTreeToQTree(
      const int src_node_id,
      const int dest_node_id,
      const jymbo::types::QueryTree & src_q_tree,
      jymbo::types::QueryTree & dest_q_tree
   )
   {
      std::vector<copyFrontierNode_t> frontier;
      frontier.reserve(src_q_tree.size());

      dest_q_tree[dest_node_id] = src_q_tree[src_node_id];

      {
         const auto & src_node = src_q_tree.getNode(src_node_id);

         if (
            (src_node.childNodeIds[0] != -1) &&
            (src_node.childNodeIds[1] != -1)
         )
         {
            // Have to do it in this order, otherwise the children have their
            // positions swapped in the output tree.
            frontier.push_back(
               {src_node.childNodeIds[1], dest_node_id}
            );
            frontier.push_back(
               {src_node.childNodeIds[0], dest_node_id}
            );
         }
      }

      while (frontier.size() > 0)
      {
         const auto transplant = frontier.back();
         frontier.pop_back();

         const int new_dest_parent_id = dest_q_tree.addChild(
            transplant.destParentNodeId, src_q_tree[transplant.srcNodeId]
         );

         const auto & src_node = src_q_tree.getNode(transplant.srcNodeId);

         if (
            (src_node.childNodeIds[0] != -1) &&
            (src_node.childNodeIds[1] != -1)
         )
         {
            // Have to do it in this order, otherwise the children have their
            // positions swapped in the output tree.
            frontier.push_back(
               {src_node.childNodeIds[1], new_dest_parent_id}
            );
            frontier.push_back(
               {src_node.childNodeIds[0], new_dest_parent_id}
            );
         }
      }
   }

   jymbo::types::queryNode_t convertDNodeToQNode(
      const jymbo::types::derivativeNode_t d_node
   )
   {
      jymbo::types::queryNode_t q_node;

      if (d_node.nodeType == jymbo::types::enumDerivativeNodeType_t::kOperator)
      {
         q_node.nodeType = jymbo::types::enumQueryNodeType_t::kOperator;
         q_node.op = d_node.op;
      }
      else if (d_node.nodeType == jymbo::types::enumDerivativeNodeType_t::kSymbol)
      {
         q_node.nodeType = jymbo::types::enumQueryNodeType_t::kSymbol;
         q_node.symbol = d_node.symbol;
      }

      return q_node;
   }

   void convertToQTree(
      const jymbo::types::DerivativeTree & d_tree,
      const jymbo::types::QueryTree & q_tree_in,
      jymbo::types::QueryTree & q_tree_out
   )
   {
      // The source node IDs belong to the derivative tree.
      // The destination node IDs belong to the output query tree.
      std::vector<copyFrontierNode_t> frontier;
      frontier.reserve(d_tree.size() + q_tree_in.size());

      q_tree_out.setRoot(convertDNodeToQNode(d_tree[d_tree.getRootId()]));

      // Have to do it in this order, otherwise the children have their
      // positions swapped in the output tree.
      frontier.push_back(
         {d_tree.getRoot().childNodeIds[1], q_tree_out.getRootId()}
      );
      frontier.push_back(
         {d_tree.getRoot().childNodeIds[0], q_tree_out.getRootId()}
      );

      while (frontier.size() > 0)
      {
         const copyFrontierNode_t copy_node = frontier.back();
         frontier.pop_back();

         const auto & d_node = d_tree.getNode(copy_node.srcNodeId);

         if (d_node.meta.nodeType == jymbo::types::enumDerivativeNodeType_t::kReference)
         {
            // If we've found a reference to q Q node, then this node on the
            // d-tree is a leaf node, and we don't need to check if it has any
            // children.
            const jymbo::types::queryNode_t ref_q_node = q_tree_in[d_node.meta.qNodeId];
            const int dest_node_id = q_tree_out.addChild(copy_node.destParentNodeId, ref_q_node);
            copyQTreeToQTree(d_node.meta.qNodeId, dest_node_id, q_tree_in, q_tree_out);
         }
         else
         {
            const auto temp_q_node = convertDNodeToQNode(d_node.meta);
            const int new_dest_parent_node_id = q_tree_out.addChild(
               copy_node.destParentNodeId, temp_q_node
            );

            const auto & d_tree_node = d_tree.getNode(copy_node.srcNodeId);
            if (
               (d_tree_node.childNodeIds[0] != -1) &&
               (d_tree_node.childNodeIds[1] != -1)
            )
            {
               // Have to do it in this order, otherwise the children have their
               // positions swapped in the output tree.
               frontier.push_back(
                  {d_tree_node.childNodeIds[1], new_dest_parent_node_id}
               );
               frontier.push_back(
                  {d_tree_node.childNodeIds[0], new_dest_parent_node_id}
               );
            }
         }
      }
   }

}
