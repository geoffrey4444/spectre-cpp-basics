#include <iostream>
#include <string>
#include <tuple>
#include <utility>

namespace Rectangle {
struct Length {};
struct Height {};
struct Area {};
}  // namespace Rectangle

template <typename T>
double area(const T& box) noexcept {
  const double length =
      std::get<std::pair<Rectangle::Length, double>>(box).second;
  const double height =
      std::get<std::pair<Rectangle::Height, double>>(box).second;
  return length * height;
}

int main() {
  std::tuple<std::string, double> test_tuple{"Width", 4.0};
  std::cout << std::get<0>(test_tuple) << " " << std::get<1>(test_tuple)
            << "\n";

  using Length = std::pair<Rectangle::Length, double>;
  using Height = std::pair<Rectangle::Height, double>;
  std::tuple<Length, Height> box{};
  std::get<Length>(box).second = 4.0;
  std::get<Height>(box).second = 5.0;

  std::cout << std::get<Height>(box).second << "\n";

  std::cout << area(box) << "\n";

  std::tuple<Length> box_no_height{};
  std::get<Length>(box_no_height).second = 4.0;

  // Compiler error: height not in box
  // std::cout << area(box_no_height) << "\n";

  return 0;
}
