#include <iomanip>
#include <iostream>

#include "Rectangle.hpp"

int main() {
  const Rectangle rect{4.0, 3.0};

  Rectangle rect2{5.0, 6.0};

  double x{4.0};

  std::cout << std::setprecision(15) << std::fixed;
  std::cout << "Width of rect: " << rect.width() << "\n";
  std::cout << "Width of height: " << rect.height() << "\n";
  std::cout << "Perimeter of rect: " << rect.perimeter() << "\n";

  std::cout << "Perimeter of rect2: " << rect2.evil_perimeter() << "\n";
  std::cout << "Perimeter of rect2: " << rect2.evil_perimeter() << "\n";

  std::cout << "Number of sides: " << rect.number_of_sides() << "\n";
}
