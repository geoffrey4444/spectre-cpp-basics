#include <cmath>
#include <iomanip>
#include <iostream>

/// function \f$ \sqrt{1 - x^2} \f$ for testing numerical integration
double f(const double x) noexcept {
  // x = x * 2.0; // nope: x is const
  return sqrt(fabs(1.0 - x * x));
}

/// Function to numerically integrate using left midpoint rule
/// Computes \f$\int_a^b dx f(x)\f$. Here `lower_bound` == \f$a\f$,
/// `upper_bound` == \f$b\f$, `step_size` == \f$dx\f$.
double left(const double step_size, const double lower_bound,
            const double upper_bound) noexcept {
  double result = 0.0;
  for (double x = lower_bound; x < upper_bound; x += step_size) {
    result += step_size * f(x);
  }
  return result;
}

int main() {
  constexpr double test_number = 0.5;

  constexpr double test_lower_bound = 0.0;
  constexpr double test_upper_bound = 1.0;
  constexpr double test_step_size = 1.0e-11;

  const double pi_numerical =
      4.0 * left(test_step_size, test_lower_bound, test_upper_bound);
  std::cout << std::setprecision(15);
  std::cout << pi_numerical << "\n";
  std::cout << "Error: " << pi_numerical - M_PI << "\n";

  return 0;
}
