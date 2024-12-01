#!/bin/bash

# 编译项目
cmake -B build -DENABLE_CLANG_TIDY=ON -DENABLE_SANITIZER=ON
cmake --build build

# 运行单元测试
cd build && ctest --output-on-failure

# 运行 clang-tidy 检查
if command -v clang-tidy &> /dev/null; then
    find ../src -name '*.cpp' -exec clang-tidy {} \;
fi

# 运行带 sanitizer 的测试
./src/sort_compare_test 