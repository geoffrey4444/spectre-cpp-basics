#include <iostream>

#include "tagged_tuple.hpp"

namespace Rectangle {
struct Length {
  using type = double;  // Rectangle::Length::type if you want to know the tpye
                        // of data stored by tag Length
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
  tuples::tagged_tuple<Rectangle::Length, Rectangle::Height, Rectangle::Area>
      box{};
  tuples::get<Rectangle::Length>(box) = 4.0;
  tuples::get<Rectangle::Height>(box) = 5.0;
  tuples::get<Rectangle::Area>(box) = area(box);

  std::cout << tuples::get<Rectangle::Area>(box) << "\n";

  tuples::tagged_tuple<Rectangle::Length> box_no_height{};
  tuples::get<Rectangle::Length>(box_no_height) = 4.0;

  // Compiler error: height not in box
  // std::cout << area(box_no_height) << "\n";

  return 0;
}
