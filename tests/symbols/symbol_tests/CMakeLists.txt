set(
   target
   symbol_tests
)

set(
   lib_links
   jymbosymbols
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
