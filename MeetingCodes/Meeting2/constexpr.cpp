#include <cstddef>
#include <iostream>

constexpr size_t sum_numbers_constexpr() noexcept {
  size_t result = 0;
  for (size_t i = 0; i < 100000; ++i) {
    // Note: unsafe to underflow size_t, e.g. subtracting 0 - 1 gives
    // max size of size_t
    result += i;
  }
  return result;
}

size_t sum_numbers() noexcept {
  size_t result = 0;
  for (size_t i = 0; i < 100000; ++i) {
    // Note: unsafe to underflow size_t, e.g. subtracting 0 - 1 gives
    // max size of size_t
    result += i;
  }
  return result;
}

int main() {
  size_t result = 0;
  constexpr size_t iterations = 20000;
  for (size_t i = 0; i < iterations; ++i) {
    // result = sum_numbers();
    constexpr size_t result_constexpr = sum_numbers_constexpr();
    if (i == iterations - 1) {
      std::cout << result_constexpr << "\n";
    }
  }
  // std::cout << sum_numbers() << "\n";

  return 0;
}
