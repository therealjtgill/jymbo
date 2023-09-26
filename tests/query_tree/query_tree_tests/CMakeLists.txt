set(
   target
   query_tree_tests
)

set(
   lib_links
   jymbotypes
   jymbotestutils
)

set(
   config_files
)

build_jymbo_test(
   ${target}
   "${target}.cpp"
   ""
   "${lib_links}"
   "${config_files}"
)
