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
  // for (auto it = container.begin(); it != container.end(); ++it) {
  //   result << *it << " ";
  // }

  std::string output = result.str();
  output.pop_back();

  return output + "]";
}

template <typename T>
T operator+(const T& lhs, const T& rhs) noexcept {
  T result{lhs};
  auto it_result = result.begin();
  auto it_rhs = rhs.begin();
  for (; it_result != result.end(); ++it_result, ++it_rhs) {
    *it_result += *it_rhs;
  }
  return result;
}

int main() {
  std::vector<double> test_vector{1.0, 4.0, 9.0};
  std::cout << to_string(test_vector) << "\n";

  test_vector.push_back(16.0);
  std::cout << to_string(test_vector) << "\n";

  test_vector.pop_back();
  test_vector.pop_back();

  std::cout << to_string(test_vector) << "\n";

  std::array<double, 3> test_array{{1.0, 2.0, 3.0}};
  std::cout << to_string(test_array) << "\n";

  std::array<double, 3> test2_array{{2.0, 4.0, 6.0}};
  std::array<double, 3> sum = test_array + test2_array;
  std::cout << to_string(sum) << "\n";

  std::array<double, 2> short_array{{1.0, 4.0}};

  // std::cout << to_string(sum + short_array) << "\n"; // nope: type T conflict

  return 0;
}
