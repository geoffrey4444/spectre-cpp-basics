#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

template <typename T>
void print_container(const T& container) noexcept {
  for (auto element : container) {
    std::cout << element << " ";
  }
  std::cout << "\n";
}

int main() {
  std::array<double, 20> data;
  std::iota(data.begin(), data.end(), 0.0);
  print_container(data);

  // square the data in place
  double power = 2.0;
  auto apply_math_op = [power](const double x) { return pow(x, power); };
  std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  print_container(data);

  // sqrt the data in place
  power = 0.5;
  std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  print_container(data);

  // evil math op: changes power, remove first const on next line and this
  // compiles
  // const auto evil_math_op = [power](const double x) {
  //   power += 1;
  //   return pow(x, power);
  // };
  // power = 2.0;
  // std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  // print_container(data);

  power = 2.0;
  std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  print_container(data);

  return 0;
}
