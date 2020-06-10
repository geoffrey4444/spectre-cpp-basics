#include "Rectangle.hpp"

double Rectangle::perimeter() const { return 2.0 * (width_ + height_); }

double Rectangle::evil_perimeter() const {
  const double result = 2.0 * (width_ + height_);
  // width += 4.0; // nope: can't modiy object with const function
  // height *= -2.0; // nope: can't modiy object with const function
  return result;
}
