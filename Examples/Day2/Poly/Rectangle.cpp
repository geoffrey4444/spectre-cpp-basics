// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "Rectangle.hpp"

Rectangle::Rectangle(const double length, const double width) noexcept
    : length_(length), width_(width){}

double Rectangle::perimeter() const noexcept {
  return 2.0 * (length_ + width_);
}

double Rectangle::area() const noexcept { return length_ * width_; }

// Note: same as Rectangle::area() except, if you remove the const before
// noexcept, it can silently change the rectangle after computing the area
double Rectangle::evil_area() const noexcept {
  const double area = length_ * width_;
  // length_ *= 1.1; // const member functions cannot assign to non-static
  return area;
}
