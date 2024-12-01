#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "compare_validator.h"
#include "debug_compare.h"

class SortElement
{
public:
  bool sign = {false};
  int value;
  std::string name;
};

// 包装原始的比较函数
template<typename T>
static auto create_invalidated_compare() {
  auto original_compare = [](const T &a, const T &b)
  {
    if (!b.sign)
      return true;
    if (!a.sign && b.sign)
      return false;
    return a.value < b.value;
  };

  // 使用 DebugCompareWrapper 包装比较函数
  return DebugCompareWrapper<decltype(original_compare), T>(original_compare);
}

template<typename T>
static auto create_validated_compare() {
  return [](const T &a, const T &b) {
    return a.value < b.value;
  };
}

// Main function
int main(int argc, char **argv)
{
  auto compare = create_invalidated_compare<SortElement>();
  std::vector<SortElement> vec = {{false, 1, "a"}, {false, 2, "b"}, {false, 3, "c"}};
  
  // 在排序前验证比较函数的正确性
  try {
    CompareValidator<SortElement, decltype(compare)>::validate(vec, compare);
  } catch (const std::runtime_error& e) {
    std::cerr << "Comparison function validation failed: " << e.what() << std::endl;
  }

  std::sort(vec.begin(), vec.end(), compare);
  
  for (const auto &element : vec)
  {
    std::cout << element.value << " " << element.name << std::endl;
  }

  auto compare2 = create_validated_compare<SortElement>();
  try {
    CompareValidator<SortElement, decltype(compare2)>::validate(vec, compare2);
  } catch (const std::runtime_error& e) {
    std::cerr << "Comparison function validation failed: " << e.what() << std::endl;
  }
  std::sort(vec.begin(), vec.end(), compare2);
  for (const auto &element : vec)
  {
    std::cout << element.value << " " << element.name << std::endl;
  }
}
