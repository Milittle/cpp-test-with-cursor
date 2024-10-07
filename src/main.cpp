#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <thread>
#include <chrono>

// 第三方库
#include <benchmark/benchmark.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

template<typename T>
std::string format_vector(const std::vector<T>& vec, const std::string& format_str, const std::string& separator = ", ") {
    std::vector<std::string> formatted;
    std::transform(vec.begin(), vec.end(), std::back_inserter(formatted),
                   [&format_str](const T& item) { return fmt::format(fmt::runtime(format_str), item); });
    return fmt::format("{}", fmt::join(formatted, separator));
}

static void BM_FormatVector(benchmark::State& state) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (auto _ : state) {
        benchmark::DoNotOptimize(format_vector(numbers, "{}"));
    }
}
BENCHMARK(BM_FormatVector);

static void BM_CopyString(benchmark::State& state) {
    std::string str = "12345";
    for (auto _ : state) {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(str);
        std::string str2 = str;
    }
}
BENCHMARK(BM_CopyString);

// test string to string_view
static void BM_StringView(benchmark::State& state) {
    std::string str = "12345";
    for (auto _ : state) {
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(str);
        std::string_view str_view = str;
    }
}
BENCHMARK(BM_StringView);

int main(int argc, char** argv) {
    fmt::print("Hello, {}!\n", "fmt");

    // 创建一个整数vector
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 打印整个vector
    fmt::print("Numbers: {}\n", numbers);

    // 使用join打印vector元素，用逗号分隔
    fmt::print("Numbers (comma-separated): {}\n", fmt::join(numbers, ", "));

    // 使用封装的函数格式化并打印vector，不使用前置0
    fmt::print("Numbers (formatted): {}\n", format_vector(numbers, "{}"));

    // 运行基准测试
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}