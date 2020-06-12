#pragma once

#include "Rectangle.hpp"

class Square : public Rectangle {
 public:
  Square(double length) noexcept;
  double Perimeter() noexcept;
};
