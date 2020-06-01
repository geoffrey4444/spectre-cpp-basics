#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

double trap(const std::function<double(const double)>& func, const double dx,
            const double a, const double b) noexcept {
  double result = 0.0;
  for (double x = a; x < b; x += dx) {
    result += func(x) * dx;
    result += 0.5 * dx * (func(x + dx) - func(x));
  }
  return result;
}
