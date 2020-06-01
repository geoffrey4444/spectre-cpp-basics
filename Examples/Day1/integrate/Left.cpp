#include <functional>

// Integrate function f using the trapezoid rule
double left(const std::function<double(const double)>& func, const double dx,
            const double a, const double b) noexcept {
  double result = 0.0;
  for (double x = a; x < b; x += dx) {
    result += func(x) * dx;
  }
  return result;
}
