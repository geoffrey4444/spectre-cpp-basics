#include <iostream>

#include "Rectangle.hpp"
#include "Square.hpp"

int main() {
  Rectangle rect{4.0, 5.0};

  Square sq{4.0};

  std::cout << rect.Perimeter() << "\n";

  std::cout << sq.Perimeter() << "\n";
  return 0;
}
