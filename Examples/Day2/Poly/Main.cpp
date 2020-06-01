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

  RightTriangle tri{3.0, 4.0};
  std::cout << "Right triangle perimeter: " << tri.perimeter() << "\n";
  std::cout << "Right triangle area: " << tri.area() << "\n";

  return 0;
}
