#include <iostream>
#include <string>

using namespace std::literals::string_literals;

template <typename T>
T square(const T& x) {
  return x * x;
}

template <typename T>
T add_to_self(const T& x) {
  return x + x;
}

template <typename T>
T halve(const T& x) {
  return x / 2;
}

template <>
double halve(const double& x) {
  return 0.5 * x;
}

int main() {
  std::cout << square(4.0) << "\n";
  std::cout << add_to_self(5.0) << "\n";
  std::cout << halve(3.0) << "\n";

  std::cout << halve(3) << "\n";

  std::cout << halve<double>(3) << "\n";
  std::cout << halve<int>(3.0) << "\n";

  std::cout << add_to_self("Hello"s) << "\n";
  // without string_literals, this would work:
  // std::cout << add_to_self(std::string{"Hello"}) << "\n";

  return 0;
}
