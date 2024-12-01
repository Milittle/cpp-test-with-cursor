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

add_executable(
  compare_tests
  compare_test.cpp
)

target_link_libraries(
  compare_tests
  PRIVATE
  gtest_main
  compare_validator
  fmt::fmt
)

gtest_discover_tests(compare_tests)