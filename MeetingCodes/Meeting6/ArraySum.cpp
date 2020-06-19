#include <array>
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(const T& container) noexcept {
  std::stringstream stream{};

  auto it = container.begin();
  stream << "[";
  for (; it != container.end(); ++it) {
    stream << *it << " ";
  }

  // for (element : container){
  //   stream << element << " ";
  // }
  std::string result = stream.str();
  result.pop_back();

  return result + "]";
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
  std::array<double, 3> test_array{{1.0, 4.0, 9.0}};
  std::array<double, 3> test_array_2{{4.4, 5.4, 6.4}};

  std::array<double, 2> test_array_short{{1.0, 2.0}};
  std::array<int, 2> test_array_short_int{{1, 2}};

  std::cout << to_string(test_array + test_array_2) << "\n";

  //std::cout << to_string(test_array_short_int + test_array_short) << "\n"; // nope

  std::cout << to_string(operator+(test_array, test_array_2)) << "\n";

  return 0;
}
