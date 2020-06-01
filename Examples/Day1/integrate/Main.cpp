// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

#include "Left.hpp"
#include "Trap.hpp"

// The integrand
double f(const double x) noexcept {
  // evil_print(x); // error: argument would lost const qualifier
  return sqrt(fabs(1.0 - x * x));
}

double g(const double x) noexcept { return exp(x); }

int main() {
  constexpr double dx = 1.0e-7;
  constexpr double a = 0.0;
  constexpr double b = 1.0;

  std::cout << "Integrating with dx = " << dx << "\n";

  const double result_trap = 4.0 * trap(f, dx, a, b);
  const double result_left = 4.0 * left(f, dx, a, b);

  std::cout << std::setprecision(15);

  std::cout << "result_trap = " << result_trap << "\n";
  std::cout << "result - pi = " << result_trap - M_PI << "\n";
  std::cout << "result_left = " << result_left << "\n";
  std::cout << "result_left - pi = " << result_left - M_PI << "\n";

  return 0;
}
