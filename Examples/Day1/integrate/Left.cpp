// Distributed under the MIT License.
// See LICENSE.txt for details.
#include "Left.hpp"

// Integrate function f using the trapezoid rule
double left(double (*const func)(double), const double dx,
            const double a, const double b) noexcept {
  double result = 0.0;
  for (double x = a; x < b; x += dx) {
    result += func(x) * dx;
  }
  return result;
}
