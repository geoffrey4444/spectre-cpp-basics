// Distributed under the MIT License.
// See LICENSE.txt for details.
#pragma once

#include <cstddef>

/// A base class for representing a polygon that knows how to compute its
/// perimeter and area
class Polygon {
 public:
  virtual double perimeter() const noexcept = 0;
  virtual double area() const noexcept = 0;

  static const size_t number_of_sides();
};
