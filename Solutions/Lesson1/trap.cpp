// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <cmath>
#include <iomanip>
#include <iostream>

// Legal but evil print statement that changes x after printing it
void evil_print(double& x) noexcept {
  std::cout << x << "\n";
  x += 0.1;
}

// The integrand
double f(const double x) noexcept {
  // evil_print(x); // error: argument would lost const qualifier
  return sqrt(fabs(1.0 - x * x));
}

double g(const double x) noexcept { return exp(x); }

// Integrate function f using the trapezoid rule
double trap(double (*const func)(double), const double dx, const double a,
            const double b) noexcept {
  double result = 0.0;
  for (double x = a; x < b; x += dx) {
    result += func(x) * dx;
    result += 0.5 * dx * (func(x + dx) - func(x));
  }
  return result;
}

double trap(const double dx, const double a, const double b) noexcept {
  return trap(f, dx, a, b);
}

int main() {
  constexpr double dx = 1.0e-7;
  constexpr double a = 0.0;
  constexpr double b = 1.0;

  // evilprint(dx); // dx would lose const qualifier
  std::cout << "Integrating with dx = " << dx << "\n";

  // constexpr double result = 4.0 * left(dx, 0.0, 1.0); // rhs not constexpr
  const double result = 4.0 * trap(dx, a, b);
  const double result_f = 4.0 * trap(f, dx, a, b);
  const double result_g = 1.0 + trap(g, dx, a, b);

  std::cout << std::setprecision(15);

  std::cout << "result = " << result << "\n";
  std::cout << "result - pi = " << result - M_PI << "\n";
  std::cout << "result - result_f = " << result - result_f << "\n";
  std::cout << "result_g = " << result_g << "\n";

  return 0;
}
