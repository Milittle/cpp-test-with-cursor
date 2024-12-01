#include <vector>
#include <tuple>

template<typename Compare, typename T>
class DebugCompareWrapper {
public:
  explicit DebugCompareWrapper(Compare comp) : comp_(comp) {}

  bool operator()(const T& a, const T& b) {
    bool result = comp_(a, b);
    comparison_history_.push_back({a, b, result});
    return result;
  }

private:
  Compare comp_;
  std::vector<std::tuple<T, T, bool>> comparison_history_;
}; 