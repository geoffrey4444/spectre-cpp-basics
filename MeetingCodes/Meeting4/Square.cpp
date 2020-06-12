#include "Square.hpp"

Square::Square(const double length) noexcept : Rectangle(length, length) {}

double Square::Perimeter() noexcept { return 4.0 * length_; }
