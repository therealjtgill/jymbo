set(
   target
   operator_tests
)

set(
   lib_links
   jymbotypes
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
