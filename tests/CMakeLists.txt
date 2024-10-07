add_executable(
  unit_tests
  test_format_vector.cpp
)

target_link_libraries(
  unit_tests
  PRIVATE
  gtest_main
  fmt::fmt
)

include(GoogleTest)
gtest_discover_tests(unit_tests)