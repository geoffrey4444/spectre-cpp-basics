#include <cstddef>
#include <iostream>
#include <string>

template <size_t N>
size_t decrement() noexcept {
  return N - 1;
}

template <>
size_t decrement<0>() noexcept {
  return 0;
}

template <size_t N>
size_t factorial() noexcept {
  return N * factorial<N - 1>();
}

template <>
size_t factorial<0>() noexcept {
  return 1;
}

int main() {
  std::cout << decrement<4>() << "\n";

  std::cout << decrement<0>() << "\n";

  std::cout << factorial<5>() << "\n";

  return 0;
}
