#include <iostream>

template <typename T>
T square(const T x) { return x * x; }

int main() {
  int test = 4;
  std::cout << square(test) << "\n";

  double test_2 = 4.5;
  std::cout << square(test_2) << "\n";

  return 0;
}
