cmake_minimum_required(VERSION 3.22)  # FetchContent requires CMake 3.11+

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 clang-tidy 支持
option(ENABLE_CLANG_TIDY "Enable clang-tidy on build" OFF)
if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
  if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY 
      ${CLANG_TIDY_EXE};
      -p=${CMAKE_BINARY_DIR}
    )
  else()
    message(WARNING "clang-tidy not found!")
  endif()
endif()

# 添加 Sanitizer 选项
option(ENABLE_SANITIZER "Enable Address Sanitizer" OFF)

# 定义 Sanitizer 标志，但不全局应用
if(ENABLE_SANITIZER)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(SANITIZER_FLAGS -fsanitize=address,leak -fsanitize-recover=address -O1 -fno-omit-frame-pointer -g)
  else()
    message(WARNING "Sanitizer is only supported on GCC and Clang")
  endif()
endif()

include(FetchContent)

# 获取 fmt 库
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2  # 指定一个特定的版本标签
)

# 获取 Google Benchmark
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3  # 使用最新的稳定版本
)

# 获取 Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0  # 使用最新的稳定版本
)

# 设置 Google Benchmark 选项
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

# 设置 Google Test 选项
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# 使 fmt、benchmark 和 googletest 可用
FetchContent_MakeAvailable(fmt benchmark googletest)

add_subdirectory(src)

# 添加测试
enable_testing()
add_subdirectory(tests)

# 添加 compare validator 相关目标
add_library(compare_validator INTERFACE)
target_include_directories(compare_validator INTERFACE ${CMAKE_SOURCE_DIR}/include)

# 添加 debug compare 相关目标
add_library(debug_compare INTERFACE)
target_include_directories(debug_compare INTERFACE ${CMAKE_SOURCE_DIR}/include)

# 添加 clang-tidy 自定义检查器
if(ENABLE_CLANG_TIDY)
  add_library(compare_checker SHARED tools/compare_checker.cpp)
  target_link_libraries(compare_checker PRIVATE clang-tidy)
endif()