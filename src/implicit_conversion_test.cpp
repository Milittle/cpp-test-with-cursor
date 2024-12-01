#include <fmt/core.h>
#include <cstdint>

// 枚举类型测试
enum class Color { Red = 1, Green = 2, Blue = 3 };
enum OldColor { OLD_RED = 1, OLD_GREEN = 2, OLD_BLUE = 3 };

// 测试函数
void process_int32(int32_t num, std::string_view name) {
  fmt::print("Processing int32: {}, name: {}\n", num, name);
}

void process_uint32(uint32_t num, std::string_view name) {
  fmt::print("Processing uint32: {}, name: {}\n", num, name);
}

void process_float(float num, std::string_view name) {
  fmt::print("Processing float: {}, name: {}\n", num, name);
}

void process_color(Color color) {
  fmt::print("Processing color: {}\n", static_cast<int>(color));
}

void process_double(double num, std::string_view name) {
  fmt::print("Processing double: {}, name: {}\n", num, name);
}

// 获取测试数据
int64_t get_big_number() {
  return INT64_C(1234567890123);
}

double get_precise_number() {
  return 123.456789;
}

int main() {
  fmt::print("Testing various implicit conversions:\n\n");

  // 1. 整数截断转换测试
  int64_t big_num = get_big_number();
  process_int32(big_num, "big_num");  // 警告：int64_t到int32_t的隐式转换

  // 2. 符号转换测试
  int32_t negative_num = -1;
  process_uint32(negative_num, "negative_num");  // 警告：有符号到无符号的转换

  // 3. 浮点数截断测试
  double precise_num = get_precise_number();
  process_float(precise_num, "precise_num");  // 警告：double到float的转换可能丢失精度
  
  // 4. 浮点数到整数的转换
  double pi = 3.14159;
  int32_t rounded = pi;  // 警告：浮点数到整数的隐式转换

  // 5. 枚举类型转换测试
  OldColor old_red = OLD_RED;
  int color_value = old_red;  // 警告：枚举到整数的隐式转换
  
  // 6. 不同枚举类型间的转换
  Color new_red = Color::Red;
  // OldColor mixed = new_red;  // 错误：不允许不同枚举类型间的隐式转换

  // 7. 字面量转换测试
  int64_t literal_test = 123;  // 警告：int到int64的隐式转换
  
  // 8. 算术运算中的隐式转换
  uint32_t unsigned_num = 100;
  int32_t signed_num = -50;
  auto result = unsigned_num + signed_num;  // 警告：混合符号运算

  // 9. float 到 double 的隐式提升测试
  float small_pi = 3.14f;
  process_double(small_pi, "small_pi");  // 警告：float 到 double 的隐式提升

  // 10. 混合精度算术运算
  float f_num = 3.14f;
  double d_num = 2.718;
  auto mixed_result = f_num * d_num;  // float 会被提升为 double

  return 0;
}