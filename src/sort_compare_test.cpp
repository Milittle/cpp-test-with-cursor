#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

class SortElement
{
public:
  bool sign = {false};
  int value;
  std::string name;
};

// Main function
int main(int argc, char **argv)
{
  static auto compare = [](const SortElement &a, const SortElement &b)
  {
    if (!b.sign)
      return true;
    if (!a.sign && b.sign)
      return false;
    return a.value < b.value;
  };
  std::vector<SortElement> vec = {{false, 1, "a"}, {false, 2, "b"}, {false, 3, "c"}};
  std::sort(vec.begin(), vec.end(), compare);
  for (const auto &element : vec)
  {
    std::cout << element.value << " " << element.name << std::endl;
  }
}