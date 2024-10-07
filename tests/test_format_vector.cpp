#include <gtest/gtest.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>
#include <algorithm>

// 从 main.cpp 复制 format_vector 函数
template<typename T>
std::string format_vector(const std::vector<T>& vec, const std::string& format_str, const std::string& separator = ", ") {
    std::vector<std::string> formatted;
    std::transform(vec.begin(), vec.end(), std::back_inserter(formatted),
                   [&format_str](const T& item) { return fmt::format(fmt::runtime(format_str), item); });
    return fmt::format("{}", fmt::join(formatted, separator));
}

TEST(FormatVectorTest, IntegerVector) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    EXPECT_EQ(format_vector(numbers, "{}"), "1, 2, 3, 4, 5");
}

TEST(FormatVectorTest, FloatVector) {
    std::vector<float> numbers = {1.1f, 2.2f, 3.3f};
    EXPECT_EQ(format_vector(numbers, "{:.1f}"), "1.1, 2.2, 3.3");
}