#include <cmath>
#include <iostream>

double test_function(const double x) noexcept {
  return sqrt(fabs(1.0 - x * x));
}

struct test_functor {
  double operator()(const double x) const noexcept {
    return sqrt(fabs(1.0 - x * x));
  }
};

template <typename T>
double trap(const T& f, const double lower_bound, const double upper_bound,
            const double step_size) noexcept {
  double result = 0.0;
  for (double x = lower_bound; x <= upper_bound; x += step_size) {
    result += 0.5 * step_size * (f(x) + f(x + step_size));
  }

  return result;
}

int main() {
  std::cout << 4.0 * trap(test_function, 0.0, 1.0, 0.01) << "\n";
  std::cout << 4.0 * trap(test_functor{}, 0.0, 1.0, 0.01) << "\n";
  std::cout << 4.0 * trap([](const auto x) { return sqrt(fabs(1.0 - x * x)); },
                          0.0, 1.0, 0.01)
            << "\n";
  return 0;
}
