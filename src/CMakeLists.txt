# 添加一个函数来应用通用的目标配置
function(apply_common_settings target)
  # 添加包含目录
  target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  
  # 链接 fmt 库
  target_link_libraries(${target} PRIVATE fmt::fmt)
  
  # 如果启用了 Sanitizer，添加相应的标志
  if(ENABLE_SANITIZER)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS})
    target_link_options(${target} PRIVATE ${SANITIZER_FLAGS})
  endif()
  
  # 如果启用了 clang-tidy，确保它会检查这个目标
  if(ENABLE_CLANG_TIDY)
    set_target_properties(${target} PROPERTIES
      CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}"
    )
  endif()
endfunction()

# 添加可执行文件
add_executable(my_project main.cpp)
add_executable(asan_test asan_test.cpp)
add_executable(test_virtual test.cpp)
add_executable(implicit_conversion_test implicit_conversion_test.cpp)
add_executable(sort_compare_test sort_compare_test.cpp)

# 应用通用设置
apply_common_settings(my_project)
apply_common_settings(asan_test)
apply_common_settings(test_virtual)
apply_common_settings(implicit_conversion_test)
apply_common_settings(sort_compare_test)

# 添加特定的库依赖
target_link_libraries(my_project PRIVATE benchmark::benchmark)
target_link_libraries(sort_compare_test PRIVATE compare_validator debug_compare)

# asan_test 的特殊设置
if(ENABLE_SANITIZER)
  target_compile_definitions(asan_test PRIVATE SANITIZER_ENABLED)
endif()

# implicit_conversion_test 的特殊编译器警告设置
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(implicit_conversion_test
    PRIVATE
      -Wconversion
      -Werror=conversion
      -Wsign-conversion
      -Werror=sign-conversion
      -Wfloat-conversion
      -Werror=float-conversion
      -Wdouble-promotion
      -Werror=double-promotion
      -Wenum-conversion
      -Werror=enum-conversion
  )
elseif(MSVC)
  target_compile_options(implicit_conversion_test
    PRIVATE
      /W4
      /we4244
      /we4267
      /we4242
      /we4245
      /we4389
      /we4305
  )
endif()