#include <gtest/gtest.h>
#include "compare_validator.h"

// 测试用例
TEST(CompareTest, ValidComparison) {
  std::vector<int> elements = {1, 2, 3, 4, 5};
  auto valid_comp = [](const int& a, const int& b) { return a < b; };
  
  EXPECT_NO_THROW(CompareValidator<int, decltype(valid_comp)>::validate(elements, valid_comp));
}

// 测试错误的比较函数
TEST(CompareTest, InvalidComparison) {
  std::vector<int> elements = {1, 2, 3};
  // 错误的比较函数：违反传递性
  auto invalid_comp = [](const int& a, const int& b) { return (a + b) % 2 == 0; };
  
  EXPECT_THROW(
    CompareValidator<int, decltype(invalid_comp)>::validate(elements, invalid_comp),
    std::runtime_error
  );
} 