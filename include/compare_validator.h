#pragma once
#include <vector>
#include <stdexcept>

template<typename T, typename Compare>
class CompareValidator {
public:
  static void validate(const std::vector<T>& elements, Compare comp) {
    // 检查反对称性
    for (size_t i = 0; i < elements.size(); ++i) {
      for (size_t j = 0; j < elements.size(); ++j) {
        if (i != j) {
          if (comp(elements[i], elements[j]) && comp(elements[j], elements[i])) {
            throw std::runtime_error("Comparison violates antisymmetry");
          }
        }
      }
    }

    // 检查传递性
    for (size_t i = 0; i < elements.size(); ++i) {
      for (size_t j = 0; j < elements.size(); ++j) {
        for (size_t k = 0; k < elements.size(); ++k) {
          if (comp(elements[i], elements[j]) && comp(elements[j], elements[k])) {
            if (!comp(elements[i], elements[k])) {
              throw std::runtime_error("Comparison violates transitivity");
            }
          }
        }
      }
    }

    // 检查不可自反性
    for (const auto& element : elements) {
      if (comp(element, element)) {
        throw std::runtime_error("Comparison violates irreflexivity");
      }
    }
  }
}; 