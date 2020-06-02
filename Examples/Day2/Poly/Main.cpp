// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <iostream>

#include "Polygon.hpp"
#include "Rectangle.hpp"
#include "RightTriangle.hpp"
#include "Square.hpp"

int main() {
  constexpr double length{4.0};
  constexpr double width{3.0};
  Rectangle rect{length, width};

  constexpr double length2 = 7.0;
  constexpr double width2 = 5.0;
  Rectangle rect2{length2, width2};

  std::cout << "Rectangle perimeter: " << rect.perimeter() << "\n";
  std::cout << "Rectangle area take 1: " << rect.area() << "\n";
  std::cout << "Rectangle area take 2: " << rect.evil_area() << "\n";
  std::cout << "Rectangle area take 3: " << rect.area() << "\n";
  // std::cout << "Rect length: " << rect.length_ << "\n"; // length_ private
  std::cout << "Rectangle number of sides: " << rect.number_of_sides() << "\n";

  Square sq{length};
  std::cout << "Square perimeter: " << sq.perimeter() << "\n";

  // Note: static functions can't be virtual, and the base class does not
  // define number_of_sides(). You must define number_of_sides() for each
  // derived class, and you can't call them for objects whose type is just the
  // base class type. The following fails to compile for this reason:
  // std::cout << "Square number of sides: "
  //           << static_cast<const Polygon&>(sq).number_of_sides();
  std::cout << "Square number of sides: " << sq.number_of_sides() << "\n";

  RightTriangle tri{3.0, 4.0};
  std::cout << "Right triangle perimeter: " << tri.perimeter() << "\n";
  std::cout << "Right triangle area: " << tri.area() << "\n";

  return 0;
}
