// Distributed under the MIT License.
// See LICENSE.txt for details.
#pragma once

#include <cstddef>

class Rectangle {
 public:
  Rectangle(double length, double width) noexcept;

  double perimeter() const noexcept;
  double area() const noexcept;

  static const size_t number_of_sides() { return 4; }

  // same as area(), but remove the const before noexcept, and the function
  // is allowed to silently change the member variables
  double evil_area() const noexcept;

 private:
  double length_;
  double width_;
};
