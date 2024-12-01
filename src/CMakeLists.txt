add_executable(my_project main.cpp)
add_executable(asan_test asan_test.cpp)
add_executable(test_virtual test.cpp)
add_executable(implicit_conversion_test implicit_conversion_test.cpp)

target_include_directories(my_project PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(asan_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(implicit_conversion_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(my_project PRIVATE fmt::fmt benchmark::benchmark)
target_link_libraries(asan_test PRIVATE fmt::fmt)
target_link_libraries(implicit_conversion_test PRIVATE fmt::fmt)

# 只为 asan_test 启用 Sanitizer
if(ENABLE_SANITIZER)
  target_compile_options(asan_test PRIVATE ${SANITIZER_FLAGS})
  target_link_options(asan_test PRIVATE ${SANITIZER_FLAGS})
  target_compile_definitions(asan_test PRIVATE SANITIZER_ENABLED)
endif()

# 设置编译器警告标志 - 针对不同类型的隐式转换
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(implicit_conversion_test
    PRIVATE
      #-Wall
      #-Wextra
      # 整数转换警告
      -Wconversion
      -Werror=conversion
      # 符号转换警告
      -Wsign-conversion
      -Werror=sign-conversion
      # 浮点转换警告
      -Wfloat-conversion
      -Werror=float-conversion
      -Wdouble-promotion
      -Werror=double-promotion
      # 枚举转换警告
      -Wenum-conversion
      -Werror=enum-conversion
  )
elseif(MSVC)
  target_compile_options(implicit_conversion_test
    PRIVATE
      /W4
      /we4244  # 整数转换可能丢失数据
      /we4267  # 大小类型转换可能丢失数据
      /we4242  # 有符号/无符号不匹配的转换
      /we4245  # 有符号/无符号不匹配的转换
      /we4389  # 有符号/无符号不匹配的比较
      /we4305  # 截断常量值
  )
endif()

# 如果启用了Sanitizer，添加相应的标志
if(ENABLE_SANITIZER)
  target_compile_options(implicit_conversion_test PRIVATE ${SANITIZER_FLAGS})
  target_link_options(implicit_conversion_test PRIVATE ${SANITIZER_FLAGS})
endif()