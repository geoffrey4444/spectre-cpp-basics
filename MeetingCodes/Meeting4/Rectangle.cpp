#include "Rectangle.hpp"

Rectangle::Rectangle(const double length, const double width) noexcept
    : length_(length), width_(width) {}

double Rectangle::Perimeter() const noexcept {
  return 2.0 * (length_ + width_);
}
