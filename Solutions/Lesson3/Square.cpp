// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <iostream>
#include <string>

template <typename T>
T square(const T& x) noexcept {
  return x * x;
}

template <typename T>
T add_to_self(const T& x) noexcept {
  return x + x;
}

template <typename T>
T halve(const T& x) noexcept {
  return x / 2;
}

int main() {
  std::cout << square(4.4) << "\n";
  std::cout << square(5) << "\n";

  std::cout << add_to_self(4.4) << "\n";
  std::cout << add_to_self(5) << "\n";
  std::string hello = "Hello, world!";
  std::cout << add_to_self(hello) << "\n";

  std::cout << halve(3.0) << "\n";
  std::cout << halve(3) << "\n";
  std::cout << halve<double>(3) << "\n";
  // std::cout << halve<int>(3.3)
  //           << "\n";  // warning: implicit conversion changes value
  std::cout << halve<int>(static_cast<int>(3.3)) << "\n";

  return 0;
}
