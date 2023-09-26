#ifndef POLYNOMIAL_QUERY_TREE_HEADER
#define POLYNOMIAL_QUERY_TREE_HEADER

#include "jymbo_types.hpp"

namespace test_utils
{

   void addAPowXN(
      const int n,
      int plus_node_id,
      const jymbo::types::queryNode_t & indep_sym_node,
      jymbo::types::QueryTree & q_tree
   );

   // Generates a query tree with an nth order polynomial in it.
   void polynomialQueryTree(const int n, jymbo::types::QueryTree & q_tree);

}

#endif
