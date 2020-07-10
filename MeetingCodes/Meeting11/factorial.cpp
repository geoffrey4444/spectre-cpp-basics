#include <cstddef>
#include <iostream>

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
  std::cout << decrement<2>() << "\n";

  std::cout << factorial<4>() << "\n";
  return 0;
}
