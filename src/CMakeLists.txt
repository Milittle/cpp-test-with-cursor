add_executable(my_project main.cpp)
add_executable(asan_test asan_test.cpp)

target_include_directories(my_project PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(asan_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(my_project PRIVATE fmt::fmt benchmark::benchmark)
target_link_libraries(asan_test PRIVATE fmt::fmt)

# 只为 asan_test 启用 Sanitizer
if(ENABLE_SANITIZER)
  target_compile_options(asan_test PRIVATE ${SANITIZER_FLAGS})
  target_link_options(asan_test PRIVATE ${SANITIZER_FLAGS})
  target_compile_definitions(asan_test PRIVATE SANITIZER_ENABLED)
endif()