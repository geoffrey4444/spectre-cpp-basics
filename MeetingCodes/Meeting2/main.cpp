#include <cmath>
#include <iomanip>
#include <iostream>

#include "trap.hpp" 

double f(const double x) noexcept { return sqrt(fabs(1.0 - x * x)); }

int main() {
  constexpr double step = 1.0e-6;
  constexpr double lower = 0.0;
  constexpr double upper = 1.0;

  const double result = 4.0 * trap(f, step, lower, upper);
  const double error = result - M_PI;
  std::cout << std::setprecision(15) << result << "\n";
  std::cout << error << "\n";

  return 0;
}
