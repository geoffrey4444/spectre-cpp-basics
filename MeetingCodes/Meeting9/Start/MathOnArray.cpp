#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

template <typename T>
void print_container(const T& container) noexcept {
  for (auto element : container) {
    std::cout << element << " ";
  }
  std::cout << "\n";
}

int main() {
  // ....
  
  return 0;
}
