#include "trap.hpp"

#include <cmath>

double trap(double (*const func)(const double), const double step_size,
            const double lower_bound, const double upper_bound) noexcept {
  double result = 0.0;
  for (double x = lower_bound; x < upper_bound; x += step_size) {
    result += func(x) * step_size;
    result += 0.5 * step_size * (func(x + step_size) - func(x));
  }

  return result;
}
