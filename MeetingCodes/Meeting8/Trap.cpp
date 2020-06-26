#include <cmath>
#include <iostream>

template <typename T>
double trap(const T& f, const double lower_bound, const double upper_bound,
            const double step_size) noexcept {
  double result = 0.0;
  for (double x = lower_bound; x <= upper_bound; x += step_size) {
    result += 0.5 * step_size * (f(x) + f(x + step_size));
  }
  return result;
}

double test_func(const double x) noexcept { return sqrt(fabs(1.0 - x * x)); }

template <size_t Coef>
struct test_struct {
  static double coef = Coef;
  double operator()(const double x) const noexcept {
    return coef * sqrt(fabs(1.0 - x * x));
  }
};

int main() {
  std::cout << 4.0 * trap(test_func, 0.0, 1.0, 1.0e-5) << "\n";
  std::cout << trap(test_struct<4>{}, 0.0, 1.0, 1.0e-5) << "\n";
  std::cout << 4.0 * trap(sqrt, 0.0, 1.0, 1.0e-5) << "\n";

  std::cout << 4.0 * trap([](const auto x) { return sqrt(fabs(1.0 - x * x)); },
                          0.0, 1.0, 1.0e-5)
            << "\n";
  return 0;
}