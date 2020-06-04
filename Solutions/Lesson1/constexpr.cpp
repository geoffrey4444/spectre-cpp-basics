#include <cstddef>
#include <iostream>

// This function is evaluated at run time
const double slow_init() noexcept {
  size_t turtle = 0;
  for (size_t i = 0; i < 100000; ++i) {
    turtle += 1;
  }
  constexpr double result = 4.0;
  return result;
}

// This function is evaluated by the compiler at compile time
constexpr double slow_init_constexpr() noexcept {
  // This loop is just to slow down the function
  // If you make the upper bound of i too large, the compiler will complain,
  // since it has a limit of how many times it will loop while evaluating
  // constexpr functions
  size_t turtle = 0;
  for (size_t i = 0; i < 100000; ++i) {
    turtle += 1;
  }
  constexpr double result = 4.0;
  return result;
}

int main() {
  // This loop simply makes the program take longer, so run time differences
  // are easier to notice
  constexpr size_t j_max = 100000;
  for (size_t j = 0; j < j_max; ++j) {
    // The next line will get run at run time
    const double test_result = slow_init();
    
    // The compiler evaluates the next line at compile time
    // constexpr double test_result_expr = slow_init_constexpr();

    // Only print the result one time, at the last time through the loop
    if (j == j_max - 1) {
      std::cout << test_result << "\n";
      // std::cout << test_result_expr << "\n";
    }
  }

  return 0;
}
