#pragma once

#include "Polygon.hpp"

class Rectangle : public Polygon {
  public:
   Rectangle(double length, double width) noexcept;
   double Perimeter() const noexcept override;

  protected:
   double length_;
   double width_;
};
