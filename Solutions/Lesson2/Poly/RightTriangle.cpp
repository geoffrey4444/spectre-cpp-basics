// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <cmath>

#include "RightTriangle.hpp"

RightTriangle::RightTriangle(const double length_a,
                             const double length_b) noexcept
    : length_a_(length_a), length_b_(length_b) {}

double RightTriangle::perimeter() const noexcept {
  return length_a_ + length_b_ +
         sqrt(length_a_ * length_a_ + length_b_ * length_b_);
}

double RightTriangle::area() const noexcept {
  return 0.5 * length_a_ * length_b_;
}
