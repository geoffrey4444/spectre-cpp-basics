#include <array>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void print(const T& container) noexcept {
  std::cout << "[ ";
  for (auto element : container) {
    std::cout << element << " ";
  }
  std::cout << "]";
}

int main() {
  std::vector<double> x{{1.0, 4.0, 9.0}};
  print(x);

  x.push_back(16.0);
  print(x);

  std::cout << x[1] << "\n";

  std::array<double, 3> coord{{4.0, 3.0, 2.0}};
  print(coord);
  std::cout << "\n";

  coord[1] = 4.444;
  print(coord);
  std::cout << "\n";

  std::cout << coord[0] << "\n";

  std::array<std::string, 2> words{"Hello", "world"};
  print(words);
  std::cout << "\n";

  std::array<std::array<double, 3>, 3> matrix{
      {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}};
  print(matrix[1]);
  std::cout << "\n";
  std::cout << matrix[1][2] << "\n";

  return 0;
}
