#include <iostream>

#include "tagged_tuple.hpp"

namespace Rectangle {
struct Length {
  using type = double;
};
struct Height {
  using type = double;
};
struct Area {
  using type = double;
};
}  // namespace Rectangle

template <typename T>
double area(const T& box) noexcept {
  return tuples::get<Rectangle::Length>(box) *
         tuples::get<Rectangle::Height>(box);
}

int main() {
  tuples::tagged_tuple<Rectangle::Length, Rectangle::Height> simple_box{};
  tuples::get<Rectangle::Length>(simple_box) = 6.0;
  tuples::get<Rectangle::Height>(simple_box) = 7.0;

  std::cout << area(simple_box) << "\n";

  tuples::tagged_tuple<Rectangle::Length> simple_box_no_height{};
  tuples::get<Rectangle::Length>(simple_box_no_height) = 6.0;

  // Compiler error: height not in box
  // std::cout << simple_area(simple_box_no_height) << "\n";

  return 0;
}
