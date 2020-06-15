// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::string to_string(const T& container) noexcept {
  std::stringstream result;
  result << "[";
  for (auto element : container) {
    result << element << " ";
  }
  std::string output = result.str();
  output.pop_back();
  return output + "]";
}

int main() {
  std::vector<double> x{{1.0, 4.0, 9.0}};
  std::cout << to_string(x) << "\n";

  x.push_back(16.0);
  std::cout << to_string(x) << "\n";

  std::cout << x[1] << "\n";

  std::array<double, 3> coord{{4.0, 3.0, 2.0}};
  std::cout << to_string(coord) << "\n";
  std::cout << "\n";

  coord[1] = 4.444;
  std::cout << to_string(coord) << "\n";
  std::cout << "\n";

  std::cout << coord[0] << "\n";

  std::array<std::string, 2> words{"Hello", "world"};
  std::cout << to_string(words) << "\n";
  std::cout << "\n";

  std::array<std::array<double, 3>, 3> matrix{
      {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}};
  std::cout << to_string(matrix[1]) << "\n";
  std::cout << "\n";
  std::cout << matrix[1][2] << "\n";

  return 0;
}
