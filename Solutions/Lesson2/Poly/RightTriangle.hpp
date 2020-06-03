// Distributed under the MIT License.
// See LICENSE.txt for details.
#pragma once

#include "Polygon.hpp"

class RightTriangle : public Polygon {
 public:
  RightTriangle(double length_a, double length_b) noexcept;

  double perimeter() const noexcept override;
  double area() const noexcept override;

  static const size_t number_of_sides() { return 3; }

 private:
  double length_a_;
  double length_b_;
};
