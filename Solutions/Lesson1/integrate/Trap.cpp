// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "Trap.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

double trap(double (*const func)(double), const double dx,
            const double a, const double b) noexcept {
  double result = 0.0;
  for (double x = a; x < b; x += dx) {
    result += func(x) * dx;
    result += 0.5 * dx * (func(x + dx) - func(x));
  }
  return result;
}
