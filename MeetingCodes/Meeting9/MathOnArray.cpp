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

double square(const double x) noexcept { return x * x; }

// [&power](const double x) { return pow(x, power); } ->
// struct apply_math_op {
//   double& power;
//   double operator()(const double x) { return pow(x, power); }
// };

int main() {
  std::array<double, 20> data;
  std::iota(data.begin(), data.end(), 0.0);
  print_container(data);

  double power = 2.0;
  auto apply_math_op = [&power](const double x) { return pow(x, power); };
  std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  print_container(data);

  power = 0.5;
  std::transform(data.begin(), data.end(), data.begin(), apply_math_op);
  print_container(data);

  // If this isn't const, other_math_op can be evil and change it
  const double other_power = 0.0;
  auto apply_other_math_op = [&other_power](const double x) noexcept {
    // other_power += 1; // other_power is const, so can't be changed
    return pow(x, other_power);
  };
  std::transform(data.begin(), data.end(), data.begin(), apply_other_math_op);
  print_container(data);

  return 0;
}
